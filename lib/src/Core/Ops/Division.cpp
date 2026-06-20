#include "Symbolic/Core/Ops/Division.hpp"

namespace Symbolic::Core
{
    double Division::evaluate(const SymbolContext &context) const
    {
        return getLeftChild()->evaluate(context) / getRightChild()->evaluate(context);
    }

    void Division::print(std::ostream &os) const
    {
        os << "(";
        getLeftChild()->print(os);
        os << ")/(";
        getRightChild()->print(os);
        os << ")";
    }
}