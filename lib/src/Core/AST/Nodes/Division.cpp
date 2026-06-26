#include "Symbolic/Core/AST/Nodes/Division.hpp"

namespace Symbolic::Core
{
    void Division::print(std::ostream &os) const
    {
        os << "(";
        leftChild()->print(os);
        os << ")/(";
        rightChild()->print(os);
        os << ")";
    }
}