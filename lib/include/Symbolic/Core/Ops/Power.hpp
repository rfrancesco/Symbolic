#pragma once

#include "Symbolic/Core/AST/BinaryOperatorNode.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

namespace Symbolic::Core
{
    class Power : public BinaryOperatorNode
    {
    public:
        using BinaryOperatorNode::BinaryOperatorNode;

        void accept(ASTVisitor& visitor) const override {
            visitor.visitPower(*this);
        }

        double evaluate(const SymbolContext &context) const override;

        void print(std::ostream &os) const override;
    };
}