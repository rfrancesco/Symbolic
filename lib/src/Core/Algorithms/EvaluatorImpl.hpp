#pragma once
#include "Symbolic/Core/Algorithms/Evaluator.hpp"
#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"

namespace Symbolic::Core
{
    class EvaluatorImpl : public ASTVisitor
    {
    private:
        double result{0.0};
        const Expression &expression_;
        SymbolContext context_{};

    public:
        EvaluatorImpl() = delete;
        EvaluatorImpl(const Expression &expression) : expression_(expression) {};
        double operator()(SymbolContext context);

        void visitValue(const Value &) override;
        void visitSymbol(const Symbol &) override;
        void visitNegative(const Negative &) override;
        void visitSum(const Sum &) override;
        void visitProduct(const Product &) override;
        void visitDivision(const Division &) override;
        void visitPower(const Power &) override;
        void visitFunctionNode(const FunctionNode &) override;
    };
}