#pragma once

#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "Symbolic/Core/AST/Nodes/FunctionNode.hpp"
#include "Symbolic/Core/Functions/Function.hpp"
#include <memory>
#include <vector>

namespace Symbolic::Core
{
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
        NodeStorage &operator=(const NodeStorage &) = delete;
        NodeStorage &operator=(NodeStorage &&other)
        {
            if (this != &other)
            {
                storage = std::move(other.storage);
            }
            return *this;
        }

        template <typename T>
        void takeOwnership(std::unique_ptr<T> &&other)
        {
            storage.push_back(std::move(other));
        }

        void takeOwnership(NodeStorage &&other)
        {
            for (auto &c : other.storage)
                // storage.push_back(std::move(c));
                takeOwnership(std::move(c));
            other.storage.clear();
        }

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
}