#pragma once

#include "Symbolic/Core/AST/BinaryOperatorNode.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

namespace Symbolic::Core
{
    class Division : public BinaryOperatorNode
    {
    public:
        using BinaryOperatorNode::BinaryOperatorNode;

        void accept(ASTVisitor& visitor) const override {
            visitor.visitDivision(*this);
        }

        void print(std::ostream &os) const override;
    };
}