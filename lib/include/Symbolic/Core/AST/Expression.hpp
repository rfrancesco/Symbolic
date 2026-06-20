#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Symbolic/Core/Types.hpp"
#include "Symbolic/Core/AST/Node.hpp"
#include "Symbolic/Core/AST/Symbol.hpp"
#include "Symbolic/Core/Functions/FunctionNode.hpp"

namespace Symbolic::Core
{
    // Should be refactored away from public API into internals?
    class NodeStorage
    {
    private:
        template <typename T>
        T *storeNode(std::unique_ptr<T> owner)
        {
            T *raw = owner.get();
            storage.push_back(std::move(owner));
            return raw;
        }

    public:
        std::vector<std::unique_ptr<Node>> storage;

        template <typename T, typename... Args>
        T *makeNode(Args &&...args)
        {
            return storeNode(std::make_unique<T>(std::forward<Args>(args)...));
        }

        template <typename T>
        T *makeNode(std::initializer_list<Node *> children)
        {
            return storeNode(std::make_unique<T>(children));
        }

        FunctionNode* makeFunctionNode(const Function& f, std::vector<Node*> children) {
            return storeNode(std::make_unique<FunctionNode>(f, children));
        }
    };

    class Expression
    {
    private:
        NodeStorage storage;
        std::unordered_map<SymbolName, Symbol *> symbols;

    public:
        Node *root{nullptr};

        template <typename T, typename... Args>
        T *makeNode(Args &&...args)
        {
            return storage.makeNode<T>(std::forward<Args>(args)...);
        }

        template <typename T>
        T *makeNode(std::initializer_list<Node *> children)
        {
            return storage.makeNode<T>(children);
        }

        FunctionNode* makeFunctionNode(const Function& f, std::vector<Node*> children) {
            return storage.makeFunctionNode(f, children);
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