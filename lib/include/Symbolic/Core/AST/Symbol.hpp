#pragma once

#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AST/Node.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

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

        void accept(ASTVisitor& visitor) const override {
            visitor.visitSymbol(*this);
        }

        void print(std::ostream &os) const override
        {
            os << name_;
        }
    };
}