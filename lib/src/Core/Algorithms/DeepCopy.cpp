#include "Symbolic/Core/Core.hpp"
#include "Symbolic/Core/Algorithms/DeepCopy.hpp"
#include "DeepCopyImpl.hpp"

namespace Symbolic::Core
{
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
