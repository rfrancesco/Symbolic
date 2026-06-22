#include "Symbolic/Core/Ops/Sum.hpp"

namespace Symbolic::Core
{
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