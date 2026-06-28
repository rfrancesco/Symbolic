#include "Symbolic/Core/Core.hpp"
#include "Symbolic/Core/Algorithms/DeepCopy.hpp"
#include "DeepCopyImpl.hpp"

namespace Symbolic::Core
{
    Expression DeepCopyImpl::operator()() &&
    {
        return std::move(result);
    }

    void DeepCopyImpl::visitValue(const Value &v)
    {
        returnedChildren.push_back(result.makeNode<Value>(v.value()));
    }
    void DeepCopyImpl::visitSymbol(const Symbol &s)
    {
        if (result.hasSymbol(s.name()))
            returnedChildren.push_back(result.getSymbol(s.name()));
        else
            returnedChildren.push_back(result.makeSymbol(s.name()));
    }

    template <typename T>
    void DeepCopyImpl::unaryVisitor(const T &n)
    {
        returnedChildren.clear();
        n.child()->accept(*this);
        const Node *childCopy = returnedChildren[0];
        returnedChildren = {result.makeNode<T>(childCopy)};
    }

    template <typename T>
    void DeepCopyImpl::binaryVisitor(const T &n)
    {
        const Node *lhs;
        const Node *rhs;

        returnedChildren.clear();
        n.leftChild()->accept(*this);
        lhs = returnedChildren[0];

        returnedChildren.clear();
        n.rightChild()->accept(*this);
        rhs = returnedChildren[0];

        returnedChildren = {result.makeNode<T>(lhs, rhs)};
    }

    template <typename T>
    void DeepCopyImpl::naryVisitor(const T &n)
    {
        std::vector<const Node *> childrenCopy;
        for (auto *c : n.children())
        {
            returnedChildren.clear();
            c->accept(*this);
            childrenCopy.push_back(returnedChildren[0]);
        }
        returnedChildren = {result.makeNode<T>(childrenCopy)};
    }

    void DeepCopyImpl::visitNegative(const Negative &n)
    {
        unaryVisitor<Negative>(n);
    }
    void DeepCopyImpl::visitSum(const Sum &s)
    {
        naryVisitor<Sum>(s);
    }
    void DeepCopyImpl::visitProduct(const Product &p)
    {
        naryVisitor<Product>(p);
    }
    void DeepCopyImpl::visitDivision(const Division &d)
    {
        binaryVisitor<Division>(d);
    }
    void DeepCopyImpl::visitPower(const Power &p)
    {
        binaryVisitor<Power>(p);
    }
    void DeepCopyImpl::visitFunctionNode(const FunctionNode & n) {
        std::vector<const Node *> childrenCopy;
        for (auto *c : n.children())
        {
            returnedChildren.clear();
            c->accept(*this);
            childrenCopy.push_back(returnedChildren[0]);
            // printChildren();
        }
        Function f{n.function()};
        returnedChildren = {result.makeFunctionNode(f, childrenCopy)};
    }
}
