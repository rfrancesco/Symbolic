#pragma once

#include "Symbolic/Core/AbstractStructure/Node.hpp"

namespace Symbolic::Core
{
    class Value : public Node
    {
    public:
        double value;

        explicit Value(double value) : value(value) {}

        double evaluate(const SymbolContext &) const override
        {
            return value;
        }

        void print(std::ostream &os) const override
        {
            os << value;
        }
    };

}