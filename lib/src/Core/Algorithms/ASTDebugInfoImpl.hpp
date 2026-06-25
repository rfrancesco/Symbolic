#pragma once

#include "Symbolic/Core/Algorithms/ASTDebugInfo.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"
#include <span>
#include <iostream>

namespace Symbolic::Core
{
    class ASTDebugInfoImpl : public ASTVisitor
    {
    private:
        const Node *root;
        int indentLevel{0};
        std::ostream &out;

        std::vector<const Node *> memory_;

        std::string indent()
        {
            std::ostringstream os;
            for (int i = 0; i < indentLevel; i++)
                os << "    ";
            return os.str();
        }

    public:
        ASTDebugInfoImpl() = delete;
        ASTDebugInfoImpl(const Node *root, std::ostream &out);

        std::span<const Node * const> memory() const;

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
