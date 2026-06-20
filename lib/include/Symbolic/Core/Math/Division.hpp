#pragma once

#include "Symbolic/Core/AbstractStructure/BinaryNode.hpp"

namespace Symbolic::Core
{
    class Division : public BinaryNode
    {
    public:
        using BinaryNode::BinaryNode;

        double evaluate(const SymbolContext &context) const override;

        void print(std::ostream &os) const override;
    };
}