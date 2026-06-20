#pragma once

#include "Symbolic/Core/AST/Node.hpp"

namespace Symbolic::Core
{
    class UnaryNode : public Node
    {
    public:
        Node *child;
        explicit UnaryNode(Node *child) : child(child)
        {
            if (!child)
                throw std::runtime_error("nullptr!");
        }
    };

}