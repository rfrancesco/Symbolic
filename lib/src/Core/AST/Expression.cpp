#include "Symbolic/Core/AST/Expression.hpp"

namespace Symbolic::Core
{
    const Symbol *Expression::makeSymbol(SymbolName name)
    {
        if (symbols.contains(name))
            throw std::invalid_argument("Symbol " + name + " already exists in given expression (did you mean getSymbol()?)");
        symbols[name] = makeNode<Symbol>(name);
        return symbols[name];
    }

    const Symbol *Expression::getSymbol(SymbolName name) const
    {
        auto result = symbols.find(name);
        if (result != symbols.cend())
            return result->second;
        else
            throw std::invalid_argument("Symbol " + name + " not found in given expression (did you mean makeSymbol()?)");
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