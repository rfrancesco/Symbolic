#include "Symbolic/Core/Core.hpp"
#include "Symbolic/Core/Algorithms/ASTDebugInfo.hpp"
#include <iostream>
#include <typeinfo>

namespace Symbolic::Core
{
    class ASTDebugInfoImpl : public ASTVisitor
    {
    private:
        const Node *root;
        int indentLevel{0};
        std::ostream& out;

        void printIndent()
        {
            for (int i=0; i<indentLevel; i++)
                out << "    ";
        }

        std::string indent() 
        {
            std::ostringstream os;
            for (int i=0; i<indentLevel; i++)
                os << "    ";
            return os.str();
        }

    public:
        ASTDebugInfoImpl() = delete;
        ASTDebugInfoImpl(const Node *root, std::ostream& out = std::cerr) : root(root), out(out)
        {
            out << "ASTDebugInfo: AST root at address " << root << "\n";
            out << "{" << std::endl;
            root->accept(*this);
            out << "}" << std::endl;
        };

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

    void ASTDebugInfoImpl::visitValue(const Value &v)
    {
        ++indentLevel;
        out << indent() << "Value " << v.value() << " at address " << &v << std::endl;
        --indentLevel;
    }

    void ASTDebugInfoImpl::visitSymbol(const Symbol &s)
    {
        ++indentLevel;
        out << indent() << "Symbol " << s.name() << " at address " << &s << std::endl;
        --indentLevel;
    }

    template <typename T>
    void ASTDebugInfoImpl::unaryVisitor(const T &n)
    {
        ++indentLevel;
        out << indent() << typeid(T).name() << " (Unary) at address " << &n << "\n";
        out << indent() << "Child: " << n.getChild() << "\n";
        out << indent() << "{" << std::endl;
        n.getChild()->accept(*this);
        out << indent() << "}" << std::endl;
        --indentLevel;
    }

    template <typename T>
    void ASTDebugInfoImpl::binaryVisitor(const T &n)
    {
        ++indentLevel;
        out << indent() << typeid(T).name() << " (Binary) at address " << &n << "\n";
        
        const Node *lhs{n.getLeftChild()};
        const Node *rhs{n.getRightChild()};

        out << indent() << "Children: " << lhs << "\t" << rhs << "\n";
        out << indent() << "{" << std::endl;
        lhs->accept(*this);
        rhs->accept(*this);
        out << indent() << "}" << std::endl;
        --indentLevel;
    }

    template <typename T>
    void ASTDebugInfoImpl::naryVisitor(const T &n)
    {
        ++indentLevel;
        out << indent() << typeid(T).name() << " (Nary) at address " << &n << "\n";
        
        out << indent() << "Children: ";
        for (auto* c : n.getChildren()) {
           out << c << "\t";
        }
        out << "\n";
        
        out << indent() << "{" << std::endl;
        for (auto* c : n.getChildren()) {
            c->accept(*this);
        }
        out << indent() << "}" << std::endl;
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
    void ASTDebugInfoImpl::visitFunctionNode(const FunctionNode & n)
    {
        ++indentLevel;
        out << indent() << "Function node at address " << &n << "\n";
        const Function& f = n.function();
        out << indent() << "Function: " << f.name() << " with arity = ";
        if (f.arity()) 
            out << *(f.arity()) << "\n";
        else 
            out << "[arbitrary]" << "\n";

        out << indent() << "Children: ";
        for (auto* c : n.getChildren()) {
           out << c << "\t";
        }
        out << "\n";
        
        out << indent() << "{" << std::endl;
        for (auto* c : n.getChildren()) {
            c->accept(*this);
        }
        out << indent() << "}" << std::endl;
        --indentLevel;
    }

    void ASTDebugInfo(const Node *n)
    {
        ASTDebugInfoImpl debug{n};
    };
}
