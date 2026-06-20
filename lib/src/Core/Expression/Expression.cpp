#include "Symbolic/Core/Expression/Expression.hpp"

namespace Symbolic::Core
{
    Symbol *Expression::makeSymbol(SymbolName name)
    {
        if (symbols.contains(name))
            throw std::logic_error("Cannot create symbol " + name + " in expression - It already exists");
        symbols[name] = makeNode<Symbol>(name);
        return symbols[name];
    }

    Symbol *Expression::getSymbol(SymbolName name) const
    {
        auto result = symbols.find(name);
        if (result != symbols.cend())
            return result->second;
        else
            throw std::logic_error("Symbol " + name + " not found");
    }

    double Expression::evaluate(const SymbolContext &context) const
    {
        if (tree)
            return tree->evaluate(context);
        throw std::runtime_error("Trying to evaluate empty expression");
    }

    void Expression::print(std::ostream &os, bool endl) const
    {
        tree->print(os);
        if (endl)
            os << "\n";
    }

    std::ostream &operator<<(std::ostream &os, const Expression &expression)
    {
        expression.print(os, false);
        return os;
    }

}