#include "EvaluatorImpl.hpp"
#include <cmath>

namespace Symbolic::Core
{
    double EvaluatorImpl::operator()(SymbolContext context)
    {
        context_ = context;
        expression_.root->accept(*this);
        return result;
    }

    void EvaluatorImpl::visitValue(const Value &v)
    {
        result = toDouble(v.value());
    }

    void EvaluatorImpl::visitSymbol(const Symbol &s)
    {
        result = context_.at(s.name());
    }

    void EvaluatorImpl::visitNegative(const Negative &n)
    {
        (n.child())->accept(*this);
        result = -result;
    }

    void EvaluatorImpl::visitSum(const Sum &s)
    {
        double r = 0;
        for (auto *c : s.children())
        {
            c->accept(*this);
            r += result;
        }
        result = r;
    }

    void EvaluatorImpl::visitProduct(const Product &s)
    {
        double r = 1;
        for (auto *c : s.children())
        {
            c->accept(*this);
            r *= result;
        }
        result = r;
    }

    void EvaluatorImpl::visitDivision(const Division &d)
    {
        d.leftChild()->accept(*this);
        double numerator = result;
        d.rightChild()->accept(*this);
        double denominator = result;

        result = numerator / denominator;
    }
    void EvaluatorImpl::visitPower(const Power &p)
    {
        p.leftChild()->accept(*this);
        double base = result;
        p.rightChild()->accept(*this);
        double exponent = result;

        result = std::pow(base, exponent);
    }
    void EvaluatorImpl::visitFunctionNode(const FunctionNode &f)
    {
        std::vector<double> args;
        for (auto *c : f.children())
        {
            c->accept(*this);
            args.push_back(result);
        }
        result = (f.function())(std::span<const double>(args));
    }

}