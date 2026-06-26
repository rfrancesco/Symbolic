#pragma once

#include "Symbolic/Core/AST/Nodes/Node.hpp"

namespace Symbolic::Core
{
    class UnaryOperatorNode : public Node
    {
    private:
        const Node *child_;

    public:
        explicit UnaryOperatorNode(const Node *child) : child_(child)
        {
            if (!child)
                throw std::invalid_argument("Passed nullptr to UnaryOperatorNode constructor");
        }

        const Node * child() const { return child_; }

        virtual std::span<const Node *const> children() const override {
            return std::span<const Node *const>{{child_}};
        }
    };

}