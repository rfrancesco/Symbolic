#pragma once
#include "Symbolic/Core/AST/Nodes/UnaryOperatorNode.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

namespace Symbolic::Core
{
    class Negative : public UnaryOperatorNode
    {
    public:
        using UnaryOperatorNode::UnaryOperatorNode;

        void accept(ASTVisitor& visitor) const override {
            visitor.visitNegative(*this);
        }

        void print(std::ostream &os) const override
        {
            os << "-";
            getChild()->print(os);
        }
    };

}