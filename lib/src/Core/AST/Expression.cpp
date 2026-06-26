#include "Symbolic/Core/AST/Expression.hpp"

namespace Symbolic::Core
{
    const Symbol *Expression::makeSymbol(SymbolName name)
    {
        const Symbol* s = makeNode<Symbol>(name);
        symbols.insert(s);
        return s;
    }

    const Symbol *Expression::getSymbol(SymbolName name) const
    {
        return symbols.at(name);
    }

    bool Expression::hasSymbol(SymbolName name) const {
        return symbols.contains(name);
    }

    void Expression::print(std::ostream &os, bool endl) const
    {
        root->print(os);
        if (endl)
            os << "\n";
    }

    std::ostream &operator<<(std::ostream &os, const Expression &expression)
    {
        expression.print(os, false);
        return os;
    }

}