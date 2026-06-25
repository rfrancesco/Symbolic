#pragma once

#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "Symbolic/Core/AST/Expression.hpp"

namespace Symbolic::Core
{
    Expression deepCopy(const Expression&);
    Expression deepCopy(const Node*);
}
