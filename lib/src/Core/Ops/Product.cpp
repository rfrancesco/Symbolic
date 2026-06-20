#include "Symbolic/Core/Ops/Product.hpp"

namespace Symbolic::Core
{
    double Product::evaluate(const SymbolContext &context) const
    {
        double result = 1.0;
        for (auto c : children)
            result *= c->evaluate(context);
        return result;
    }

    void Product::print(std::ostream &os) const
    {
        bool first = true;
        auto end = children.cend();
        for (auto it = children.cbegin(); it != end; ++it)
        {
            if (!first)
                os << "*";
            first = false;

            os << "(";
            (*it)->print(os);
            os << ")";
        }
    }
}