#pragma once

#include <vector>
#include <span>
#include "Symbolic/Core/AST/Nodes/Node.hpp"

namespace Symbolic::Core
{
    class NaryOperatorNode : public Node
    {
    private:
        std::vector<const Node *> children_;

    public:
        explicit NaryOperatorNode(std::initializer_list<const Node *> children) : children_(std::vector<const Node *>(children))
        {
        }

        explicit NaryOperatorNode(std::vector<const Node *> children) : children_(std::move(children))
        {
            if (children_.size() < 2)
                throw std::invalid_argument("NaryOperatorNode constructor requires at least 2 children nodes");
            for (auto *c : children_)
                if (!c)
                    throw std::invalid_argument("Passed nullptr to NaryOperatorNode constructor");
        }

        std::span<const Node *const> children() const override {
            return children_;
        }
    };

}