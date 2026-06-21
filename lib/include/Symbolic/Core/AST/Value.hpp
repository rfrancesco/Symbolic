#pragma once

#include "Symbolic/Core/AST/Node.hpp"
#include "Symbolic/Core/Types.hpp"

namespace Symbolic::Core
{
    class Value : public Node
    {
    private:
        const Rational value_;

    public:
        explicit Value(Rational value) : value_(value) {}

        Rational value() const {
            return value_;
        }

        double evaluate(const SymbolContext &) const override
        {
            return toDouble(value_);
        }

        void print(std::ostream &os) const override
        {
            printRational(os,value_);
        }
    };

}