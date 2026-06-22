#pragma once

#include "Symbolic/Core/Algorithms/ASTVisitor.hpp"
#include "Symbolic/Core/Core.hpp"

namespace Symbolic::Core
{
    class EvaluatorImpl;

    class Evaluator {
    private:
        std::unique_ptr<EvaluatorImpl> impl_;
    public:
        Evaluator() = delete;
        ~Evaluator();
        Evaluator(const Expression& expression);
        double operator()(SymbolContext context);
    };
}
