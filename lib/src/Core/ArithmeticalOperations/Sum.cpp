#include "Symbolic/Core/ArithmeticalOperations/Sum.hpp"

namespace Symbolic::Core
{
    double Sum::evaluate(const SymbolContext &context) const
    {
        double result = 0;
        for (auto c : children)
            result += c->evaluate(context);
        return result;
    }

    void Sum::print(std::ostream &os) const
    {
        bool first = true;
        auto end = children.cend();
        for (auto it = children.cbegin(); it != end; ++it)
        {
            if (!first)
                os << "+";
            first = false;

            os << "(";
            (*it)->print(os);
            os << ")";
        }
    }
}