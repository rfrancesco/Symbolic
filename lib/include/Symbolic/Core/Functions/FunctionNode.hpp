#pragma once

#include <vector>
#include <span>
#include <functional>
#include "Symbolic/Core/AST/Node.hpp"
#include "Symbolic/Core/Functions/Function.hpp"

/* Some notes on this
   - public/private needs to be sorted out
   - it is a bit flaky. Inside, it operates with spans. This means that
     1) sin(x), etc: one needs to pass a lambda that unpacks it
     2) max(x), min(x): one needs to pass std::ranges::max or min (C++20)

    - In general the templates and interface for making this are very ugly.
      This needs to be resolved.
    - arity is never checked anywhere. The idea was to avoid e.g. passing 2 or zero arguments to sin(x)
      However maybe templates + concepts are better suited for this?
   */

namespace Symbolic::Core
{

    class FunctionNode : public Node
    {
    private:
        Function function;
        std::vector<Node *> children;

    public:
        explicit FunctionNode(const Function &function, std::vector<Node *> children) : function(function), children(children)
        {
            for (auto *c : children)
                if (!c)
                    throw std::invalid_argument("Passed nullptr to FunctionNode constructor");
        }

        std::span<Node *const> getChildren() const { return std::span<Node *const>(children.begin(), children.end()); }

        double evaluate(const SymbolContext &context) const override
        {
            std::vector<double> args;
            for (auto *c : children)
                args.push_back(c->evaluate(context));

            return function(std::span<const double>(args));
        }

        void print(std::ostream &os) const override
        {
            bool first = true;
            os << function.name << "(";
            for (auto *c : children)
            {
                if (!first)
                    os << ",";
                first = false;
                c->print(os);
            }
            os << ")";
        }
    };
}