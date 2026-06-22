#include "Symbolic/Core/Ops/Power.hpp"

#include <cmath>

namespace Symbolic::Core
{
    void Power::print(std::ostream &os) const
    {
        os << "(";
        getLeftChild()->print(os);
        os << ")^(";
        getRightChild()->print(os);
        os << ")";
    }
}