#include "Symbolic/Core/ArithmeticalOperations/Division.hpp"

namespace Symbolic::Core
{
    double Division::evaluate(const SymbolContext &context) const
    {
        return lChild->evaluate(context) / rChild->evaluate(context);
    }

    void Division::print(std::ostream &os) const
    {
        os << "(";
        lChild->print(os);
        os << ")/(";
        rChild->print(os);
        os << ")";
    }
}