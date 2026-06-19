#pragma once
#include "Symbolic/Core/AbstractStructure/UnaryNode.hpp"

namespace Symbolic::Core
{
    class Negative : public UnaryNode
    {
    public:
        Negative(Node *child) : UnaryNode(child) {}
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