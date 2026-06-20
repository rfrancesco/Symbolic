#pragma once
#include "Symbolic/Core/AST/UnaryNode.hpp"

namespace Symbolic::Core
{
    class Negative : public UnaryNode
    {
    public:
        using UnaryNode::UnaryNode;
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