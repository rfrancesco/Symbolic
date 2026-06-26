#include "Symbolic/Core/Core.hpp"
#include "Symbolic/Core/Algorithms/DeepCopy.hpp"
// #include <iostream>

namespace Symbolic::Core
{
    class DeepCopyImpl : public ASTVisitor
    {
    private:
        const Node *root;
        Expression result;

        // Internal registers
        const Node *tmpNode;
        std::vector<const Node *> returnedChildren;

    public:
        DeepCopyImpl() = delete;
        DeepCopyImpl(const Node *root) : root(root)
        {
            root->accept(*this);
            result.root = returnedChildren[0];
            // std::cout << "Copied everything" << std::endl;
            // std::cout << result << std::endl;
        };
        DeepCopyImpl(const Expression &expression) : DeepCopyImpl(expression.root) {
                                                     };
        Expression operator()() &&;

        // void printChildren()
        // {
        //     for (auto c : returnedChildren)
        //         std::cout << c << " ";
        //     std::cout << std::endl;
        // }

        void visitValue(const Value &) override;
        void visitSymbol(const Symbol &) override;
        void visitNegative(const Negative &) override;
        void visitSum(const Sum &) override;
        void visitProduct(const Product &) override;
        void visitDivision(const Division &) override;
        void visitPower(const Power &) override;
        void visitFunctionNode(const FunctionNode &) override;

        template <typename T>
        void unaryVisitor(const T &);
        template <typename T>
        void binaryVisitor(const T &);
        template <typename T>
        void naryVisitor(const T &);
    };

    Expression DeepCopyImpl::operator()() &&
    {
        return std::move(result);
    }

    void DeepCopyImpl::visitValue(const Value &v)
    {
        returnedChildren.push_back(result.makeNode<Value>(v.value()));
        // std::cout << "Value: Copying &" << &v << " to " << returnedChildren[0] << " " << v.value() << std::endl;
    }
    void DeepCopyImpl::visitSymbol(const Symbol &s)
    {
        if (result.hasSymbol(s.name()))
            returnedChildren.push_back(result.getSymbol(s.name()));
        else
            returnedChildren.push_back(result.makeSymbol(s.name()));
        // std::cout << "Symbol: Copying &" << &s << " to " << returnedChildren[0] << " " << s.name() << std::endl;
    }

    template <typename T>
    void DeepCopyImpl::unaryVisitor(const T &n)
    {
        returnedChildren.clear();
        n.child()->accept(*this);
        // printChildren();
        const Node *childCopy = returnedChildren[0];
        returnedChildren = {result.makeNode<T>(childCopy)};
        // std::cout << "Unary: Copying &" << &n << " to " << returnedChildren[0] << std::endl;
        // std::cout << "Children: " << childCopy << std::endl;
    }

    template <typename T>
    void DeepCopyImpl::binaryVisitor(const T &n)
    {
        const Node *lhs;
        const Node *rhs;

        returnedChildren.clear();
        n.leftChild()->accept(*this);
        lhs = returnedChildren[0];
        // printChildren();

        returnedChildren.clear();
        n.rightChild()->accept(*this);
        rhs = returnedChildren[0];
        // printChildren();

        returnedChildren = {result.makeNode<T>(lhs, rhs)};
        // std::cout << "Binary: Copying &" << &n << " to " << returnedChildren[0] << std::endl;
        // std::cout << "Children: " << lhs << " " << rhs << std::endl;
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
            // printChildren();
        }
        returnedChildren = {result.makeNode<T>(childrenCopy)};
        // std::cout << "Nary: Copying &" << &n << " to " << returnedChildren[0] << std::endl;
        // std::cout << "Children: ";
        // for (auto c : childrenCopy)
        //     std::cout << c << " ";
        // std::cout << std::endl;
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

    Expression deepCopy(const Expression &expression)
    {
        if (expression.empty())
                throw std::invalid_argument("Cannot perform deep copy on an empty expression\n");
        return DeepCopyImpl{expression}();
    }

    Expression deepCopy(const Node *n)
    {
        if (!n)
                throw std::invalid_argument("Cannot perform deep copy on nullptr\n");
        return DeepCopyImpl{n}();
    };
}
