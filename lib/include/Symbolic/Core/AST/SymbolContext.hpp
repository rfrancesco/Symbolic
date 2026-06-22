#pragma once

#include <ostream>
#include <unordered_map>
#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AST/Nodes/Symbol.hpp"

namespace Symbolic::Core
{
    std::ostream &operator<<(std::ostream &os, const SymbolContext &context);
}