#pragma once
#include "Symbolic/Core/Core.hpp"
#include "Symbolic/Core/Algorithms/DeepCopy.hpp"

#include <vector>

namespace Symbolic::Core {
        class DeepCopyImpl : public ASTVisitor
    {
    private:
        const Node *root;
        Expression result;

        // Internal registers
        const Node *tmpNode;
        std::vector<const Node *> returnedChildren;

    public:
        DeepCopyImpl() = delete;
        DeepCopyImpl(const Node *root) : root(root)
        {
            root->accept(*this);
            result.root = returnedChildren[0];
        };
        DeepCopyImpl(const Expression &expression) : DeepCopyImpl(expression.root) {
                                                     };
        Expression operator()() &&;

        void visitValue(const Value &) override;
        void visitSymbol(const Symbol &) override;
        void visitNegative(const Negative &) override;
        void visitSum(const Sum &) override;
        void visitProduct(const Product &) override;
        void visitDivision(const Division &) override;
        void visitPower(const Power &) override;
        void visitFunctionNode(const FunctionNode &) override;

        template <typename T>
        void unaryVisitor(const T &);
        template <typename T>
        void binaryVisitor(const T &);
        template <typename T>
        void naryVisitor(const T &);
    };
}