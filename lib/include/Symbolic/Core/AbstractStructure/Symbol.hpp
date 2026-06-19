#pragma once

#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AbstractStructure/Node.hpp"

namespace Symbolic::Core
{
    class Symbol : public Node
    {
    public:
        SymbolName name;

        Symbol(SymbolName name) : name(name) {}

        double evaluate(const SymbolContext &context) const
        {
            return context.at(name); // bello ma c'è il problema che se manca un simbolo nel context l'exception è vaga
        }

        void print(std::ostream &os) const override
        {
            os << name;
        }
    };
}