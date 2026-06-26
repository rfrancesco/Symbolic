#include "Symbolic/Core/Core.hpp"
#include "Symbolic/Core/Algorithms/ASTDebugInfo.hpp"
#include "ASTDebugInfoImpl.hpp"
#include <iostream>
#include <typeinfo>
#include <span>

namespace Symbolic::Core
{
    ASTDebugInfoImpl::ASTDebugInfoImpl(const Node *root, std::ostream &out) : root(root), out(out)
    {
        out << "ASTDebugInfo: AST root at address " << root << "\n";
        if (!root) {
            out << "{" << std::endl;
            root->accept(*this);
            out << "}" << std::endl;
            out << "Memory: \n";
            for (auto m : memory())
                out << m << "\n";
        }
        out << "ASTDebugInfo: END" << std::endl;
    };

    std::span<const Node * const> ASTDebugInfoImpl::memory() const
    {
        return std::span<const Node* const>(memory_);
    }

    void ASTDebugInfoImpl::visitValue(const Value &v)
    {
        ++indentLevel;
        out << indent() << "Value " << v.value() << " at address " << &v << std::endl;
        memory_.push_back(&v);
        --indentLevel;
    }

    void ASTDebugInfoImpl::visitSymbol(const Symbol &s)
    {
        ++indentLevel;
        out << indent() << "Symbol " << s.name() << " at address " << &s << std::endl;
        memory_.push_back(&s);
        --indentLevel;
    }

    template <typename T>
    void ASTDebugInfoImpl::unaryVisitor(const T &n)
    {
        ++indentLevel;
        out << indent() << typeid(T).name() << " (Unary) at address " << &n << "\n";
        out << indent() << "Child: " << n.child() << "\n";
        out << indent() << "{" << std::endl;
        n.child()->accept(*this);
        out << indent() << "}" << std::endl;
        memory_.push_back(&n);
        --indentLevel;
    }

    template <typename T>
    void ASTDebugInfoImpl::binaryVisitor(const T &n)
    {
        ++indentLevel;
        out << indent() << typeid(T).name() << " (Binary) at address " << &n << "\n";

        const Node *lhs{n.leftChild()};
        const Node *rhs{n.rightChild()};

        out << indent() << "Children: " << lhs << "\t" << rhs << "\n";
        out << indent() << "{" << std::endl;
        lhs->accept(*this);
        rhs->accept(*this);
        out << indent() << "}" << std::endl;
        memory_.push_back(&n);
        --indentLevel;
    }

    template <typename T>
    void ASTDebugInfoImpl::naryVisitor(const T &n)
    {
        ++indentLevel;
        out << indent() << typeid(T).name() << " (Nary) at address " << &n << "\n";

        out << indent() << "Children: ";
        for (auto *c : n.children())
        {
            out << c << "\t";
        }
        out << "\n";

        out << indent() << "{" << std::endl;
        for (auto *c : n.children())
        {
            c->accept(*this);
        }
        out << indent() << "}" << std::endl;
        memory_.push_back(&n);
        --indentLevel;
    }

    void ASTDebugInfoImpl::visitNegative(const Negative &n)
    {
        unaryVisitor<Negative>(n);
    }
    void ASTDebugInfoImpl::visitSum(const Sum &s)
    {
        naryVisitor<Sum>(s);
    }
    void ASTDebugInfoImpl::visitProduct(const Product &p)
    {
        naryVisitor<Product>(p);
    }
    void ASTDebugInfoImpl::visitDivision(const Division &d)
    {
        binaryVisitor<Division>(d);
    }
    void ASTDebugInfoImpl::visitPower(const Power &p)
    {
        binaryVisitor<Power>(p);
    }
    void ASTDebugInfoImpl::visitFunctionNode(const FunctionNode &n)
    {
        ++indentLevel;
        out << indent() << "Function node at address " << &n << "\n";
        const Function &f = n.function();
        out << indent() << "Function: " << f.name() << " with arity = ";
        if (f.arity())
            out << *(f.arity()) << "\n";
        else
            out << "[arbitrary]" << "\n";

        out << indent() << "Children: ";
        for (auto *c : n.children())
        {
            out << c << "\t";
        }
        out << "\n";

        out << indent() << "{" << std::endl;
        for (auto *c : n.children())
        {
            c->accept(*this);
        }
        out << indent() << "}" << std::endl;
        memory_.push_back(&n);
        --indentLevel;
    }

    // void ASTDebugInfo(const Node *n)
    // {
    //     ASTDebugInfoImpl debug{n};
    // };
}
