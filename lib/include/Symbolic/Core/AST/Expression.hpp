#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "Symbolic/Core/AST/Nodes/Symbol.hpp"
#include "Symbolic/Core/AST/Nodes/FunctionNode.hpp"

namespace Symbolic::Core
{
    // Should be refactored away from public API into internals?
    class NodeStorage
    {
    private:
        template <typename T>
        const T *storeNode(std::unique_ptr<T> owner)
        {
            T *raw = owner.get();
            storage.push_back(std::move(owner));
            return raw;
        }

        std::vector<std::unique_ptr<Node>> storage;

    public:
        NodeStorage() = default;
        NodeStorage(const NodeStorage &) = delete;
        NodeStorage(NodeStorage &&other) : storage(std::move(other.storage)) {}
        NodeStorage& operator=(const NodeStorage&) = delete;
        NodeStorage& operator=(NodeStorage&&) = delete;

        template <typename T, typename... Args>
        const T *makeNode(Args &&...args)
        {
            return storeNode(std::make_unique<T>(std::forward<Args>(args)...));
        }

        template <typename T>
        const T *makeNode(std::initializer_list<const Node *> children)
        {
            return storeNode(std::make_unique<T>(children));
        }

        const FunctionNode *makeFunctionNode(const Function &f, std::vector<const Node *> children)
        {
            return storeNode(std::make_unique<FunctionNode>(f, children));
        }
    };

    class Expression
    {
    private:
        NodeStorage storage;
        std::unordered_map<SymbolName, const Symbol *> symbols;

    public:
        const Node *root{nullptr};

        template <typename T, typename... Args>
        const T *makeNode(Args &&...args)
        {
            return storage.makeNode<T>(std::forward<Args>(args)...);
        }

        template <typename T>
        const T *makeNode(std::initializer_list<const Node *> children)
        {
            return storage.makeNode<T>(children);
        }

        const FunctionNode *makeFunctionNode(const Function &f, std::vector<const Node *> children)
        {
            return storage.makeFunctionNode(f, children);
        }

        const Symbol *makeSymbol(SymbolName name);

        const Symbol *getSymbol(SymbolName name) const;

        void print(std::ostream &os, bool endl = true) const;
    };

    std::ostream &operator<<(std::ostream &os, const Expression &expression);

}