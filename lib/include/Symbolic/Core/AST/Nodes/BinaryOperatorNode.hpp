#pragma once

#include "Symbolic/Core/AST/Nodes/Node.hpp"

namespace Symbolic::Core
{
    class BinaryOperatorNode : public Node
    {
    private:
        const Node *lChild;
        const Node *rChild;

    public:
        explicit BinaryOperatorNode(const Node *lChild, const Node *rChild) : lChild(lChild), rChild(rChild)
        {
            if (!(lChild && rChild))
                throw std::invalid_argument("Passed nullptr to BinaryOperatorNode constructor");
        }

        const Node *getLeftChild() const { return lChild; }
        const Node *getRightChild() const { return rChild; }
    };
}