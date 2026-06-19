#pragma once

#include "Symbolic/Core/AbstractStructure/NaryNode.hpp"
#include "Symbolic/Core/AbstractStructure/Expression.hpp"

namespace Symbolic::Core
{
    class Sum : public NaryNode
    {
    public:
        double evaluate(const SymbolContext &context) const override;

        template <typename T, typename... Args>
        T *makeChild(Expression &expression, Args &&...args)
        {
            T *raw_pointer = expression.makeNode<T>(std::forward<Args>(args)...);
            children.push_back(raw_pointer);
            return raw_pointer;
        }

        void print(std::ostream &os) const override;
    };
}