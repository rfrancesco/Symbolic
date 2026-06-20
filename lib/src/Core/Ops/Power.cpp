#include "Symbolic/Core/Ops/Power.hpp"

#include <cmath>

namespace Symbolic::Core
{
    double Power::evaluate(const SymbolContext &context) const
    {
        return std::pow(getLeftChild()->evaluate(context), getRightChild()->evaluate(context));
    }

    void Power::print(std::ostream &os) const
    {
        os << "(";
        getLeftChild()->print(os);
        os << ")^(";
        getRightChild()->print(os);
        os << ")";
    }
}