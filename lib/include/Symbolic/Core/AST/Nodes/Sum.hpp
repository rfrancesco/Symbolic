#pragma once

#include "Symbolic/Core/AST/Nodes/NaryOperatorNode.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

namespace Symbolic::Core
{
    class Sum : public NaryOperatorNode
    {
    public:
        using NaryOperatorNode::NaryOperatorNode;

        void accept(ASTVisitor& visitor) const override {
            visitor.visitSum(*this);
        }

        void print(std::ostream &os) const override;
    };
}