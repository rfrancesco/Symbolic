#pragma once

#include "Symbolic/Core/AST/NaryNode.hpp"

namespace Symbolic::Core
{
    class Sum : public NaryNode
    {
    public:
        using NaryNode::NaryNode;

        double evaluate(const SymbolContext &context) const override;

        void print(std::ostream &os) const override;
    };
}