#pragma once
#include <cmath>
#include "Symbolic/Core/AST/UnaryNode.hpp"

namespace Symbolic::Core
{
    class Cos : public UnaryNode
    {
    public:
        using UnaryNode::UnaryNode;
        double evaluate(const SymbolContext &context) const override
        {
            return std::cos(getChild()->evaluate(context));
        }

        void print(std::ostream &os) const override
        {
            os << "cos(";
            getChild()->print(os);
            os << ")";
        }
    };

}