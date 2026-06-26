#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "Symbolic/Core/AST/Nodes/Symbol.hpp"
#include "Symbolic/Core/AST/Nodes/FunctionNode.hpp"
#include "Symbolic/Core/AST/NodeStorage.hpp"
#include "Symbolic/Core/AST/SymbolTable.hpp"

namespace Symbolic::Core
{
    class Expression
    {
    public:
        NodeStorage storage;
        SymbolTable symbols;

        const Node *root{nullptr};

        Expression() = default;
        Expression(const Expression &) = delete;
        Expression(Expression &&other) : storage(std::move(other.storage)), symbols(std::move(other.symbols)), root(other.root)
        {
            other.root = nullptr;
        }
        Expression &operator=(const Expression &) = delete;
        Expression &operator=(Expression &&other)
        {
            if (this != &other)
            {
                storage = std::move(other.storage);
                symbols = std::move(other.symbols);
                root = other.root;
                other.root = nullptr;
            }
            return *this;
        }

        bool empty() const {
            return root == nullptr;
        }

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

        bool hasSymbol(SymbolName) const;

        void print(std::ostream &os, bool endl = true) const;
    };

    std::ostream &operator<<(std::ostream &os, const Expression &expression);

}