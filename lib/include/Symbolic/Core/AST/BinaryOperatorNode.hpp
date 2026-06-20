#pragma once

#include "Symbolic/Core/AST/Node.hpp"

namespace Symbolic::Core
{
    class BinaryOperatorNode : public Node
    {
    private:
        Node *lChild;
        Node *rChild;

    public:
        explicit BinaryOperatorNode(Node *lChild, Node *rChild) : lChild(lChild), rChild(rChild)
        {
            if (!(lChild && rChild))
                throw std::invalid_argument("Passed nullptr to BinaryOperatorNode constructor");
        }

        Node *getLeftChild() const { return lChild; }
        Node *getRightChild() const { return rChild; }
    };
}