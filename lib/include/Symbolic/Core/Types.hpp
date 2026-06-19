#pragma once

#include <string>
#include <unordered_map>

namespace Symbolic::Core
{
    typedef std::string SymbolName;
    typedef std::unordered_map<SymbolName, double> SymbolContext;
}