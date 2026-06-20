#pragma once

#include "Symbolic/Core/AST/NaryOperatorNode.hpp"

namespace Symbolic::Core
{
    class Product : public NaryOperatorNode
    {
    public:
        using NaryOperatorNode::NaryOperatorNode;

        double evaluate(const SymbolContext &context) const override;

        void print(std::ostream &os) const override;
    };
}