#pragma once

#include "Symbolic/Core/Core.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"
#include <stdexcept>

/* Note: The aim of the implementation was to not allocate nodes,
         An idea is to pass around subtrees into Expression(Expression&&)
         But symbol management needs to be centralized inside the visitor
         e.g. vector<unique_ptr<Node>> symbols so that no rewrites are needed
         afterwards and then transfered to the result */

namespace Symbolic::Core
{
    class SimplifyTrivialImpl : public ASTVisitor
    {
    private:
        const Node *root;

        // Return registers of the visitor
        enum class ReturnStatus
        {
            Continue,
            IsZero,
            IsOne
        } returnStatus;
        Expression returnExpr;

        // Symbols are shared and merged into final result
        NodeStorage symbolStorage;
        SymbolTable symbols;

        const Symbol *getOrMakeSymbol(const SymbolName &name)
        {
            if (!symbols.contains(name))
            {
                const Symbol *s = symbolStorage.makeNode<Symbol>(name);
                symbols.insert(s);
                return s;
            }

            return symbols.at(name);
        }

        static std::vector<const Node *> get_expr_roots(const std::vector<Expression> &expressions)
        {
            std::vector<const Node *> result;
            for (const auto &e : expressions)
                result.push_back(e.root);
            return result;
        }

    public:
        SimplifyTrivialImpl() = delete;
        SimplifyTrivialImpl(const Node *root) : root(root)
        {
            root->accept(*this);
            returnExpr.symbols.merge(std::move(symbols));
            returnExpr.storage.takeOwnership(std::move(symbolStorage));
        }

        Expression operator()() &&
        {
            return std::move(returnExpr);
        }

        void visitValue(const Value &n) override
        {
            returnExpr = Expression();
            returnExpr.root = returnExpr.makeNode<Value>(n.value());
            if (n.value() == Rational{0})
                returnStatus = ReturnStatus::IsZero;
            else if (n.value() == Rational{1})
                returnStatus = ReturnStatus::IsOne;
            else
                returnStatus = ReturnStatus::Continue;
        }

        void visitSymbol(const Symbol &n) override
        {
            returnExpr = Expression();
            returnExpr.root = getOrMakeSymbol(n.name());
            returnStatus = ReturnStatus::Continue;
        }

        void visitNegative(const Negative &n) override
        {
            n.child()->accept(*this);
            if (typeid(n) == typeid(*(returnExpr.root)))
            {
                // child is also negative -> remove double negative
                // the already created, unused Negative node
                // is not deallocated.
                returnExpr.root = returnExpr.root->children()[0];
            }
            else
                returnExpr.root = returnExpr.makeNode<Negative>(returnExpr.root);
        }

        void visitSum(const Sum &n) override
        {
            std::vector<Expression> returnedChildren;
            for (auto c : n.children())
            {
                c->accept(*this);
                if (returnStatus == ReturnStatus::IsZero)
                    continue;
                returnedChildren.emplace_back(std::move(returnExpr));
            }

            if (returnedChildren.empty())
            {
                returnExpr = Expression();
                returnExpr.root = returnExpr.makeNode<Value>(Rational{0});
                returnStatus = ReturnStatus::IsZero;
            }
            else if (returnedChildren.size() == 1)
            {
                returnExpr = std::move(returnedChildren[0]);
                returnStatus = ReturnStatus::Continue;
            }
            else
            {
                returnExpr = Expression();
                std::vector<const Node *> returnedChildren_ptr = get_expr_roots(returnedChildren);
                returnExpr.root = returnExpr.makeNode<Sum>(returnedChildren_ptr);
                for (auto &c : returnedChildren)
                    returnExpr.storage.takeOwnership(std::move(c.storage));
                returnStatus = ReturnStatus::Continue;
            }
        }

        void visitProduct(const Product &n) override
        {
            std::vector<Expression> returnedChildren;
            for (auto c : n.children())
            {
                c->accept(*this);
                std::cout << returnExpr.root << std::endl;
                if (returnStatus == ReturnStatus::IsZero)
                {
                    returnStatus = ReturnStatus::IsZero;
                    returnExpr = Expression{};
                    returnExpr.root = returnExpr.makeNode<Value>(Rational{0});
                    return;
                }
                if (returnStatus == ReturnStatus::IsOne)
                    continue;
                returnedChildren.emplace_back(std::move(returnExpr));
            }

            if (returnedChildren.empty())
            {
                returnExpr = Expression();
                returnExpr.root = returnExpr.makeNode<Value>(Rational{0});
                returnStatus = ReturnStatus::IsOne;
            }
            else if (returnedChildren.size() == 1)
            {
                returnExpr = std::move(returnedChildren[0]);
                returnStatus = ReturnStatus::Continue;
            }
            else
            {
                returnExpr = Expression();
                std::vector<const Node *> returnedChildren_ptr = get_expr_roots(returnedChildren);
                returnExpr.root = returnExpr.makeNode<Product>(returnedChildren_ptr);
                for (auto &c : returnedChildren)
                    returnExpr.storage.takeOwnership(std::move(c.storage));
                returnStatus = ReturnStatus::Continue;
            }
        }

        void visitDivision(const Division &n) override
        {
            n.leftChild()->accept(*this);
            Expression returnedNumerator{std::move(returnExpr)};
            ReturnStatus numeratorStatus = returnStatus;

            n.rightChild()->accept(*this);
            Expression returnedDenominator{std::move(returnExpr)};
            ReturnStatus denominatorStatus = returnStatus;

            returnExpr = Expression{};
            if (denominatorStatus == ReturnStatus::IsZero)
                throw std::logic_error("Division by zero found in expression");
            else if (numeratorStatus == ReturnStatus::IsZero)
            {
                returnExpr.root = returnExpr.makeNode<Value>(Rational{0});
            }
            else
            {
                returnExpr.root = returnExpr.makeNode<Division>(returnedNumerator.root, returnedDenominator.root);
                returnExpr.storage.takeOwnership(std::move(returnedNumerator.storage));
                returnExpr.storage.takeOwnership(std::move(returnedDenominator.storage));
            }
        }

        void visitPower(const Power &n) override
        {
            n.leftChild()->accept(*this);
            Expression returnedBase{std::move(returnExpr)};
            ReturnStatus baseStatus = returnStatus;

            n.rightChild()->accept(*this);
            Expression returnedExponent{std::move(returnExpr)};
            ReturnStatus exponentStatus = returnStatus;

            returnExpr = Expression{};
            if (exponentStatus == ReturnStatus::IsZero)
            {
                returnStatus = ReturnStatus::IsOne;
                returnExpr.root = returnExpr.makeNode<Value>(Rational{1});
            }
            else if (baseStatus == ReturnStatus::IsZero)
            {
                returnExpr.root = returnExpr.makeNode<Power>(returnExpr.makeNode<Value>(Rational{0}), returnedBase.root);
                returnExpr.storage.takeOwnership(std::move(returnedExponent.storage));
            }
            else
            {
                returnExpr.root = returnExpr.makeNode<Power>(returnedBase.root, returnedExponent.root);
                returnExpr.storage.takeOwnership(std::move(returnedBase.storage));
                returnExpr.storage.takeOwnership(std::move(returnedExponent.storage));
            }
        }

        void visitFunctionNode(const FunctionNode &n) override
        {
            Function f = n.function();
            std::vector<Expression> returnedChildren;
            for (auto c : n.children())
            {
                c->accept(*this);
                returnedChildren.emplace_back(std::move(returnExpr));
            }

            returnExpr = Expression();
            std::vector<const Node *> returnedChildren_ptr = get_expr_roots(returnedChildren);
            returnExpr.root = returnExpr.makeFunctionNode(f, returnedChildren_ptr);
            for (auto &c : returnedChildren)
                returnExpr.storage.takeOwnership(std::move(c.storage));
            returnStatus = ReturnStatus::Continue;
        }
    };

    Expression simplifyTrivial(const Expression& expr) {
        return SimplifyTrivialImpl{expr.root}();
    }

    Expression simplifyTrivial(const Node* root) {
        return SimplifyTrivialImpl{root}();
    }
}
