#pragma once

#include "Symbolic/Core/AbstractStructure/NaryNode.hpp"

namespace Symbolic::Core
{
    class Product : public NaryNode
    {
    public:
        double evaluate(const SymbolContext &context) const override;

        void print(std::ostream &os) const override;
    };
}