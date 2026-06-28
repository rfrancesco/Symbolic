#pragma once

#include "Symbolic/Core/Core.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"
#include <stdexcept>

namespace Symbolic::Core
{
    Expression simplifyTrivial(const Expression &expr);

    Expression simplifyTrivial(const Node *root);
}
