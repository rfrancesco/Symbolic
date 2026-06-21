#pragma once

#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AST/Node.hpp"

namespace Symbolic::Core
{
    class Symbol : public Node
    {
        SymbolName name_;
    public:
        explicit Symbol(SymbolName name) : name_(name) {}

        SymbolName name() const {
            return name_;
        }

        double evaluate(const SymbolContext &context) const override
        {
            return context.at(name_); 
        }

        void print(std::ostream &os) const override
        {
            os << name_;
        }
    };
}