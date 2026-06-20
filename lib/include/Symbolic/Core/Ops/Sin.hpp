#pragma once
#include <cmath>
#include "Symbolic/Core/AST/UnaryNode.hpp"

namespace Symbolic::Core
{
    class Sin : public UnaryNode
    {
    public:
        using UnaryNode::UnaryNode;
        double evaluate(const SymbolContext &context) const override
        {
            return std::sin(getChild()->evaluate(context));
        }

        void print(std::ostream &os) const override
        {
            os << "sin(";
            getChild()->print(os);
            os << ")";
        }
    };

}