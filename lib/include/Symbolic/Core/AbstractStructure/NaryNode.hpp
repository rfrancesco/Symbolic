#pragma once

#include <vector>
#include "Symbolic/Core/AbstractStructure/Node.hpp"
#include "Symbolic/Core/AbstractStructure/Expression.hpp"

namespace Symbolic::Core
{
    class NaryNode : public Node
    {
    public:
        std::vector<Node *> children;

        void addChild(Node *child)
        {
            children.push_back(child);
        }

        template <typename T, typename... Args>
        T *makeChild(Expression &expression, Args &&...args)
        {
            T *raw_pointer = expression.makeNode<T>(std::forward<Args>(args)...);
            children.push_back(raw_pointer);
            return raw_pointer;
        }
    };

}