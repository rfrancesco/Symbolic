#pragma once
#include "Symbolic/Core/AbstractStructure/UnaryNode.hpp"

namespace Symbolic::Core
{
    class Negative : public UnaryNode
    {
    public:
        using UnaryNode::UnaryNode;
        double evaluate(const SymbolContext &context) const override
        {
            return -(child->evaluate(context));
        }

        void print(std::ostream &os) const override
        {
            os << "-";
            child->print(os);
        }
    };

}