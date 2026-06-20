#pragma once

#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AST/Node.hpp"

namespace Symbolic::Core
{
    class Symbol : public Node
    {
    public:
        SymbolName name;

        explicit Symbol(SymbolName name) : name(name) {}

        double evaluate(const SymbolContext &context) const
        {
            return context.at(name); 
        }

        void print(std::ostream &os) const override
        {
            os << name;
        }
    };
}