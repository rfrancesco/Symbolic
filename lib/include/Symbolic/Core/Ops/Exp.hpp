#pragma once
#include <cmath>
#include "Symbolic/Core/AST/UnaryNode.hpp"

namespace Symbolic::Core
{
    class Exp : public UnaryNode
    {
    public:
        using UnaryNode::UnaryNode;
        double evaluate(const SymbolContext &context) const override
        {
            return std::exp(getChild()->evaluate(context));
        }

        void print(std::ostream &os) const override
        {
            os << "exp(";
            getChild()->print(os);
            os << ")";
        }
    };

}