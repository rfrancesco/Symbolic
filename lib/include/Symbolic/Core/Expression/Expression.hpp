#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AST/Node.hpp"
#include "Symbolic/Core/AST/Symbol.hpp"

namespace Symbolic::Core
{
    // Should be refactored away from public API into internals?
    class NodeStorage
    {
    public:
        std::vector<std::unique_ptr<Node>> storage;

        template <typename T, typename... Args>
        T *makeNode(Args &&...args)
        {
            std::unique_ptr<T> owner_ptr = std::make_unique<T>(std::forward<Args>(args)...);
            T *raw_pointer = owner_ptr.get();
            storage.push_back(std::move(owner_ptr));
            return raw_pointer;
        }
    };

    class Expression
    {
    public:
        NodeStorage storage;
        std::unordered_map<SymbolName, Symbol *> symbols;
        Node *tree{nullptr};

        template <typename T, typename... Args>
        T *makeNode(Args &&...args)
        {
            return storage.makeNode<T>(std::forward<Args>(args)...);
        }

        Symbol *makeSymbol(SymbolName name);

        Symbol *getSymbol(SymbolName name) const;

        double evaluate(const SymbolContext &context) const;

        double operator()(const SymbolContext &context) const
        {
            return evaluate(context);
        }

        void print(std::ostream &os, bool endl = true) const;
    };

    std::ostream &operator<<(std::ostream &os, const Expression &expression);

}