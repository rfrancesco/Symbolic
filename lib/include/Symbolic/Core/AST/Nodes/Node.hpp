#pragma once

#include <ostream>
#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"
#include <span>

namespace Symbolic::Core
{

    class Node
    {
    public:
        // todo: printing needs to be refactored into Visitor too!
        virtual void print(std::ostream &) const = 0;

        virtual void accept(ASTVisitor& visitor) const = 0;

        virtual std::span<const Node *const> children() const {
            return {};
        }

        Node() = default;
        virtual ~Node() = default;
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(Node&&) = delete;
        Node& operator=(Node&&) = delete;

    };
}
