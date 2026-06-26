#pragma once

#include "Symbolic/Core/AST/Nodes/Node.hpp"

namespace Symbolic::Core
{
    class BinaryOperatorNode : public Node
    {
    private:
        std::array<const Node*, 2> children_;

    public:
        explicit BinaryOperatorNode(const Node *lChild, const Node *rChild) : children_({lChild, rChild})
        {
            if (!(lChild && rChild))
                throw std::invalid_argument("Passed nullptr to BinaryOperatorNode constructor");
        }

        const Node *leftChild() const { return children_[0]; }
        const Node *rightChild() const { return children_[1]; }

        virtual std::span<const Node *const> children() const override {
            return children_;
        }
    };
}