#include "Symbolic/Core/Ops/Product.hpp"

namespace Symbolic::Core
{
    double Product::evaluate(const SymbolContext &context) const
    {
        double result = 1.0;
        for (auto c : getChildren())
            result *= c->evaluate(context);
        return result;
    }

    void Product::print(std::ostream &os) const
    {
        bool first = true;
        for (auto c: getChildren())
        {
            if (!first)
                os << "*";
            first = false;

            os << "(";
            c->print(os);
            os << ")";
        }
    }
}