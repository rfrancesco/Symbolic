#include "Symbolic/Core/AST/Nodes/Power.hpp"

#include <cmath>

namespace Symbolic::Core
{
    void Power::print(std::ostream &os) const
    {
        os << "(";
        leftChild()->print(os);
        os << ")^(";
        rightChild()->print(os);
        os << ")";
    }
}