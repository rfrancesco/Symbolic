#pragma once

#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"
#include "Symbolic/Core/Core.hpp"

namespace Symbolic::Core
{
    class Evaluator : public ASTVisitor
    {
    private:
        double result{0.0};
        const Expression &expression_;
        SymbolContext context_{};

    public:
        Evaluator() = delete;
        Evaluator(Expression &expression) : expression_(expression) {};
        double operator()(SymbolContext context)
        {
            context_ = context;
            expression_.root->accept(*this);
            return result;
        }

        void visitValue(const Value &v) override
        {
            result = toDouble(v.value());
        }

        void visitSymbol(const Symbol &s) override
        {
            result = context_.at(s.name());
        }

        void visitNegative(const Negative &n) override
        {
            (n.getChild())->accept(*this);
            result = -result;
        }

        void visitSum(const Sum &s) override
        {
            double r = 0;
            for (auto *c : s.getChildren())
            {
                c->accept(*this);
                r += result;
            }
            result = r;
        }

        void visitProduct(const Product &s) override
        {
            double r = 1;
            for (auto *c : s.getChildren())
            {
                c->accept(*this);
                r *= result;
            }
            result = r;
        }

        void visitDivision(const Division &d) override {
            d.getLeftChild()->accept(*this);
            double numerator = result;
            d.getRightChild()->accept(*this);
            double denominator = result;

            result = numerator/denominator;
        }
        void visitPower(const Power &p) override {
            p.getLeftChild()->accept(*this);
            double base = result;
            p.getRightChild()->accept(*this);
            double exponent = result;

            result = std::pow(base, exponent);
        }
        void visitFunctionNode(const FunctionNode& f) override {
            std::vector<double> args;
            for (auto *c : f.getChildren()) {
                c->accept(*this);
                args.push_back(result);
            }
            result = (f.function())(std::span<const double>(args));
        }
    };
}
