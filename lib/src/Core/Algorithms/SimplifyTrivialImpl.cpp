#include "Symbolic/Core/AST/Expression.hpp"
#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "SimplifyTrivialImpl.hpp"

/* Note: The aim of the implementation was to not allocate unused nodes as much as possible.
         This is achieved by using intermediate Expression objects (that manage ownership)
         which are either transfered with move semantics, or reinitialize to delete
         an entire subtree.
         
         In practice we could not completely avoid allocating unused nodes
         (e.g. in double negative simplification, the first Negative is allocated anyway
         and not used. Same for symbols that end up simplifying like in (x + y*0)).
         
         So while mitigated, there is a potential small memory leak. The leak is not propagated
         through algorithms (simplify, deepCopy, etc.) since they only operate on the nodes
         that are used in the AST. 
         
         A way to patch this is to add a blacklist to the Expression/NodeStorage move semantics,
         so that unused nodes can be marked before the move, and skipped. As for symbols,
         we should add a way to track their usage, so that they can be removed from the
         SymbolTable and marked for deletion (= blacklisted in move semantics) if unused. */


namespace Symbolic::Core
{
        const Symbol *SimplifyTrivialImpl::getOrMakeSymbol(const SymbolName &name)
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

        SimplifyTrivialImpl::SimplifyTrivialImpl(const Node *root) : root(root)
        {
            root->accept(*this);
            returnExpr.symbols.merge(std::move(symbols));
            returnExpr.storage.takeOwnership(std::move(symbolStorage));
        }

        Expression SimplifyTrivialImpl::operator()() &&
        {
            return std::move(returnExpr);
        }

        void SimplifyTrivialImpl::visitValue(const Value &n)
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

        void SimplifyTrivialImpl::visitSymbol(const Symbol &n)
        {
            returnExpr = Expression();
            returnExpr.root = getOrMakeSymbol(n.name());
            returnStatus = ReturnStatus::Continue;
        }

        void SimplifyTrivialImpl::visitNegative(const Negative &n)
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

        void SimplifyTrivialImpl::visitSum(const Sum &n)
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

        void SimplifyTrivialImpl::visitProduct(const Product &n)
        {
            std::vector<Expression> returnedChildren;
            for (auto c : n.children())
            {
                c->accept(*this);
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
                // Result cannot be 0, because the case of zero has
                // already been taken care of
                returnExpr = Expression();
                returnExpr.root = returnExpr.makeNode<Value>(Rational{1});
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

        void SimplifyTrivialImpl::visitDivision(const Division &n)
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

        void SimplifyTrivialImpl::visitPower(const Power &n)
        {
            n.leftChild()->accept(*this);
            Expression returnedBase{std::move(returnExpr)};
            ReturnStatus baseStatus = returnStatus;

            n.rightChild()->accept(*this);
            Expression returnedExponent{std::move(returnExpr)};
            ReturnStatus exponentStatus = returnStatus;

            returnExpr = Expression{};

            // x^0 = 1 (we also fix 0^0 = 1 for now)
            if (exponentStatus == ReturnStatus::IsZero)
            {
                returnStatus = ReturnStatus::IsOne;
                returnExpr.root = returnExpr.makeNode<Value>(Rational{1});
            }
            else if (baseStatus == ReturnStatus::IsZero)
            {
                returnExpr.root = returnExpr.makeNode<Power>(returnExpr.makeNode<Value>(Rational{0}), returnedBase.root);
                returnExpr.storage.takeOwnership(std::move(returnedBase.storage));
            }
            else
            {
                returnExpr.root = returnExpr.makeNode<Power>(returnedBase.root, returnedExponent.root);
                returnExpr.storage.takeOwnership(std::move(returnedBase.storage));
                returnExpr.storage.takeOwnership(std::move(returnedExponent.storage));
            }
        }

        void SimplifyTrivialImpl::visitFunctionNode(const FunctionNode &n)
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
}