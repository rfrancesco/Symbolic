#pragma once

#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

namespace Symbolic::Core
{
    class Value : public Node
    {
    private:
        const Rational value_;

    public:
        explicit Value(Rational value) : value_(value) {}

        Rational value() const {
            return value_;
        }

        void accept(ASTVisitor& visitor) const override {
            visitor.visitValue(*this);
        }

        void print(std::ostream &os) const override
        {
            printRational(os,value_);
        }
    };

}