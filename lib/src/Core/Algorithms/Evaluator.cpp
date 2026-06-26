#include "EvaluatorImpl.hpp"

namespace Symbolic::Core
{

    Evaluator::Evaluator(const Expression &expression) : impl_(std::make_unique<EvaluatorImpl>(expression)) {
        if (expression.empty())
            throw std::invalid_argument("Cannot evaluate an empty expression\n");
    }

    double Evaluator::operator()(SymbolContext context) { return (*impl_)(context); }

    Evaluator::~Evaluator() = default;

}