#pragma once

#include <vector>
#include <span>
#include "Symbolic/Core/AST/Node.hpp"

namespace Symbolic::Core
{
    class NaryNode : public Node
    {
    private:
        std::vector<Node *> children;

    public:
        explicit NaryNode(std::initializer_list<Node *> children) : children(children)
        {
            if (children.size() < 2)
                throw std::invalid_argument("NaryNode constructor requires at least 2 children nodes");
            for (auto *c : children)
                if (!c)
                    throw std::invalid_argument("Passed nullptr to NaryNode constructor");
        }

        std::span<Node * const > getChildren() const { return std::span<Node* const>(children.begin(), children.end()); }
    };

}