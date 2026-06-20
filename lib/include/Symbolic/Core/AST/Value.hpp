#pragma once

#include "Symbolic/Core/AST/Node.hpp"

namespace Symbolic::Core
{
    class Value : public Node
    {
    private:
        const double value;

    public:
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