#pragma once
#include "Symbolic/Core/AST/UnaryOperatorNode.hpp"
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

        double evaluate(const SymbolContext &context) const override
        {
            return -(getChild()->evaluate(context));
        }

        void print(std::ostream &os) const override
        {
            os << "-";
            getChild()->print(os);
        }
    };

}