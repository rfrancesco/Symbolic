#include "Symbolic/Core/AST/Expression.hpp"
#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "Symbolic/Core/Algorithms/SimplifyTrivial.hpp"
#include "SimplifyTrivialImpl.hpp"

namespace Symbolic::Core
{
    Expression simplifyTrivial(const Expression &expr)
    {
        if (expr.empty())
            throw std::invalid_argument("Cannot simplify an empty expression");
        return SimplifyTrivialImpl{expr.root}();
    }

    Expression simplifyTrivial(const Node *root)
    {
        return SimplifyTrivialImpl{root}();
    }
}