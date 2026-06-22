#pragma once

#include "Symbolic/Core/AST/Nodes/Node.hpp"

namespace Symbolic::Core
{
    class UnaryOperatorNode : public Node
    {
    private:
        const Node *child;

    public:
        explicit UnaryOperatorNode(const Node *child) : child(child)
        {
            if (!child)
                throw std::invalid_argument("Passed nullptr to UnaryOperatorNode constructor");
        }

        const Node * getChild() const { return child; }
    };

}