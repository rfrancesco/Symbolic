#pragma once

#include <ostream>
#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

namespace Symbolic::Core
{

    class Node
    {
    public:
        // warning: evaluate() will be deprecated. Use Symbolic::Core::Evaluator algorithm instead:
        // see Symbolic/Core/Algorithms/Evaluator.hpp or examples/01_basic_usage.cpp
        // 
        // Leaving this implementation here so that I can perform some more tests
        // before removing this from the inheritance tree.
        // No [[deprecated]] because it would create a bunch of irrelevant compiler warnings
        virtual double evaluate(const SymbolContext &) const = 0;
        // todo: printing needs to be refactored into Visitor too!
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
