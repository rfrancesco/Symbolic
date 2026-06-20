#include "Symbolic/Core/AST/SymbolContext.hpp"

namespace Symbolic::Core
{
    std::ostream &operator<<(std::ostream &os, const SymbolContext& context)
    {
        os << "{";
        bool first = true;
        for (auto pair : context)
        {
            if (!first)
                os << ", ";
            first = false;
            os << "(" << pair.first << " = " << pair.second << ")";
        }
        os << "}";
        return os;
    }
}