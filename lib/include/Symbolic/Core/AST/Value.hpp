#pragma once

#include "Symbolic/Core/AST/Node.hpp"
#include "Symbolic/Core/Types.hpp"

namespace Symbolic::Core
{
    class Value : public Node
    {
    private:
        const Rational value;

    public:
        explicit Value(Rational value) : value(value) {}

        double evaluate(const SymbolContext &) const override
        {
            return toDouble(value);
        }

        void print(std::ostream &os) const override
        {
            printRational(os,value);
        }
    };

}