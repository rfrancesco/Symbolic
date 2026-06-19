#pragma once

#include <ostream>
#include <unordered_map>
#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AbstractStructure/Symbol.hpp"

namespace Symbolic::Core
{

    typedef std::unordered_map<SymbolName, double> SymbolContext;

    std::ostream &operator<<(std::ostream &os, SymbolContext context);

}