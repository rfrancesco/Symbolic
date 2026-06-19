#pragma once

#include <vector>
#include "Symbolic/Core/AbstractStructure/Node.hpp"

namespace Symbolic::Core
{
    class NaryNode : public Node
    {
    public:
        std::vector<Node *> children;

        void addChild(Node *child)
        {
            children.push_back(child);
        }
    };

}