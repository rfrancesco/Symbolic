#pragma once

#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AST/Nodes/Symbol.hpp"
#include <unordered_map>
#include <stdexcept>

namespace Symbolic::Core
{
    class SymbolTable
    {
    private:
        std::unordered_map<SymbolName, const Symbol*> table;
    
    public:
        bool contains(const SymbolName& name) const {
            return table.contains(name);
        }

        void insert(const Symbol* s) {
            // User should not interact with SymbolTable
            // Assert should be enough
            assert(s != nullptr);   
            if (contains(s->name()))
                throw std::invalid_argument("Symbol " + s->name() + " is already defined in SymbolTable.");
            
            table[s->name()] = s;
        }

        const Symbol* at(const SymbolName& name) const {
            if (!contains(name))
                throw std::invalid_argument("Symbol " + name + " not found in SymbolTable.");
            return table.at(name);
        }

        void merge(SymbolTable&& other) {
            for (const auto& [name, ptr] : other.table) 
                insert(ptr);    // will throw in case of name collision
            other.table.clear();
        }


    };
}