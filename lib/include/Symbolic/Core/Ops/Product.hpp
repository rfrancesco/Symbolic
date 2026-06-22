#pragma once

#include "Symbolic/Core/AST/NaryOperatorNode.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

namespace Symbolic::Core
{
    class Product : public NaryOperatorNode
    {
    public:
        using NaryOperatorNode::NaryOperatorNode;

        void accept(ASTVisitor& visitor) const override {
            visitor.visitProduct(*this);
        }

        double evaluate(const SymbolContext &context) const override;

        void print(std::ostream &os) const override;
    };
}