#pragma once
#include <cmath>
#include "Symbolic/Core/AST/UnaryNode.hpp"

namespace Symbolic::Core
{
    class Tan : public UnaryNode
    {
    public:
        using UnaryNode::UnaryNode;
        double evaluate(const SymbolContext &context) const override
        {
            return std::tan(getChild()->evaluate(context));
        }

        void print(std::ostream &os) const override
        {
            os << "tan(";
            getChild()->print(os);
            os << ")";
        }
    };

}