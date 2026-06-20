#pragma once

#include "Symbolic/Core/AST/Node.hpp"

namespace Symbolic::Core
{
    class BinaryNode : public Node
    {
    private:
        Node *lChild;
        Node *rChild;

    public:
        explicit BinaryNode(Node *lChild, Node *rChild) : lChild(lChild), rChild(rChild)
        {
            if (!(lChild && rChild))
                throw std::runtime_error("Passed nullptr to BinaryNode constructor");
        }

        Node *getLeftChild() const { return lChild; }
        Node *getRightChild() const { return rChild; }
    };
}