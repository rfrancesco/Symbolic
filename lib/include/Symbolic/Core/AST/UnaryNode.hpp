#pragma once

#include "Symbolic/Core/AST/Node.hpp"

namespace Symbolic::Core
{
    class UnaryNode : public Node
    {
    private:
        Node *child;

    public:
        explicit UnaryNode(Node *child) : child(child)
        {
            if (!child)
                throw std::runtime_error("nullptr!");
        }

        const Node * getChild() const { return child; }
    };

}