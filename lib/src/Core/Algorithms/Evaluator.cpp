#include "EvaluatorImpl.hpp"

namespace Symbolic::Core
{

    Evaluator::Evaluator(const Expression &expression) : impl_(std::make_unique<EvaluatorImpl>(expression)) {}

    double Evaluator::operator()(SymbolContext context) { return (*impl_)(context); }

    Evaluator::~Evaluator() = default;

}