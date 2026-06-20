#include "Symbolic/Core/Math/Power.hpp"

#include <cmath>

namespace Symbolic::Core
{
    double Power::evaluate(const SymbolContext &context) const
    {
        return std::pow(lChild->evaluate(context), rChild->evaluate(context));
    }

    void Power::print(std::ostream &os) const
    {
        os << "(";
        lChild->print(os);
        os << ")^(";
        rChild->print(os);
        os << ")";
    }
}