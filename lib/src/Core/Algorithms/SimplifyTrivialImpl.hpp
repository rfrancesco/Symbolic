#pragma once

#include "Symbolic/Core/AST/Expression.hpp"
#include "Symbolic/Core/AST/Nodes/Node.hpp"
#include "Symbolic/Core/Algorithms/SimplifyTrivial.hpp"

namespace Symbolic::Core
{
    class SimplifyTrivialImpl : public ASTVisitor
    {
    private:
        const Node *root;

        // Return registers of the visitor
        enum class ReturnStatus
        {
            Continue,
            IsZero,
            IsOne
        } returnStatus;
        Expression returnExpr;

        // Symbols are shared and merged into final result
        NodeStorage symbolStorage;
        SymbolTable symbols;

        const Symbol *getOrMakeSymbol(const SymbolName &name);

    public:
        SimplifyTrivialImpl() = delete;
        SimplifyTrivialImpl(const Node *root);

        Expression operator()() &&;

        void visitValue(const Value &n) override;
        void visitSymbol(const Symbol &n) override;
        void visitNegative(const Negative &n) override;
        void visitSum(const Sum &n) override;
        void visitProduct(const Product &n) override;
        void visitDivision(const Division &n) override;
        void visitPower(const Power &n) override;
        void visitFunctionNode(const FunctionNode &n) override;
    };
}