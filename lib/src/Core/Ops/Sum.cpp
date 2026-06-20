#include "Symbolic/Core/Ops/Sum.hpp"

namespace Symbolic::Core
{
    double Sum::evaluate(const SymbolContext &context) const
    {
        double result = 0;
        for (auto c : getChildren())
            result += c->evaluate(context);
        return result;
    }

    void Sum::print(std::ostream &os) const
    {
        bool first = true;
        for (auto c: getChildren())
        {
            if (!first)
                os << "+";
            first = false;

            os << "(";
            c->print(os);
            os << ")";
        }
    }
}