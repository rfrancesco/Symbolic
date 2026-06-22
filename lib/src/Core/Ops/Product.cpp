#include "Symbolic/Core/Ops/Product.hpp"

namespace Symbolic::Core
{
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