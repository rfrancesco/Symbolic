#pragma once
#include "Symbolic/Core/AST/UnaryOperatorNode.hpp"

namespace Symbolic::Core
{
    class Negative : public UnaryOperatorNode
    {
    public:
        using UnaryOperatorNode::UnaryOperatorNode;
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