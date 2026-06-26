#include "Symbolic/Core/AST/Nodes/Product.hpp"

namespace Symbolic::Core
{
    void Product::print(std::ostream &os) const
    {
        bool first = true;
        for (auto c: children())
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