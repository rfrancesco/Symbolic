#pragma once

#include "Symbolic/Core/AST/Node.hpp"

namespace Symbolic::Core
{
    class BinaryNode : public Node
    {
    public:
        Node *lChild;
        Node *rChild;
        explicit BinaryNode(Node *lChild, Node *rChild) : lChild(lChild), rChild(rChild)
        {
            if (!(lChild && rChild))
                throw std::runtime_error("nullptr!");
        }
    };
}