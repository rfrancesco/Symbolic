#include "Symbolic/Core/Expression/Expression.hpp"

namespace Symbolic::Core
{
    Symbol *Expression::makeSymbol(SymbolName name)
    {
        if (symbols.contains(name))
            throw std::invalid_argument("Symbol " + name + " already exists in given expression (did you mean getSymbol()?)");
        symbols[name] = makeNode<Symbol>(name);
        return symbols[name];
    }

    Symbol *Expression::getSymbol(SymbolName name) const
    {
        auto result = symbols.find(name);
        if (result != symbols.cend())
            return result->second;
        else
            throw std::invalid_argument("Symbol " + name + " not found in given expression (did you mean makeSymbol()?)");
    }

    double Expression::evaluate(const SymbolContext &context) const
    {
        if (tree)
            return tree->evaluate(context);
        throw std::runtime_error("Expression is empty and cannot be evaluated (tree = nullptr)");
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