#pragma once

#include <ostream>
#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

namespace Symbolic::Core
{

    class Node
    {
    public:
        virtual double evaluate(const SymbolContext &) const = 0;
        virtual void print(std::ostream &) const = 0;

        virtual void accept(ASTVisitor& visitor) const = 0;

        Node() = default;
        virtual ~Node() = default;
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(Node&&) = delete;
        Node& operator=(Node&&) = delete;

    };
}
