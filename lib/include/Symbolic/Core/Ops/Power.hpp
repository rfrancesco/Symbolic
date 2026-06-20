#pragma once

#include "Symbolic/Core/AST/BinaryOperatorNode.hpp"

namespace Symbolic::Core
{
    class Power : public BinaryOperatorNode
    {
    public:
        using BinaryOperatorNode::BinaryOperatorNode;

        double evaluate(const SymbolContext &context) const override;

        void print(std::ostream &os) const override;
    };
}