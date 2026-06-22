#include "Symbolic/Core/Ops/Division.hpp"

namespace Symbolic::Core
{
    void Division::print(std::ostream &os) const
    {
        os << "(";
        getLeftChild()->print(os);
        os << ")/(";
        getRightChild()->print(os);
        os << ")";
    }
}