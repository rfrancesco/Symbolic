#pragma once

#include <vector>
#include <span>
#include "Symbolic/Core/AST/Nodes/Node.hpp"

namespace Symbolic::Core
{
    class NaryOperatorNode : public Node
    {
    private:
        std::vector<const Node *> children;

    public:
        explicit NaryOperatorNode(std::initializer_list<const Node *> children) : children(children)
        {
            if (children.size() < 2)
                throw std::invalid_argument("NaryOperatorNode constructor requires at least 2 children nodes");
            for (auto *c : children)
                if (!c)
                    throw std::invalid_argument("Passed nullptr to NaryOperatorNode constructor");
        }

        std::span<const Node * const > getChildren() const { return std::span<const Node* const>(children.begin(), children.end()); }
    };

}