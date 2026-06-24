#include "Symbolic/Core/Functions/Function.hpp"
#include "Symbolic/Core/Functions/CommonFunctions.hpp"
#include <span>
#include <cmath>

namespace Symbolic::Core::Functions
{
    const Function Sin{
        "sin", [](std::span<const double> s)
        {
            return std::sin(s[0]);
        },
        1};

    const Function Cos{
        "cos", [](std::span<const double> s)
        {
            return std::cos(s[0]);
        },
        1};

    const Function Tan{
        "tan", [](std::span<const double> s)
        {
            return std::tan(s[0]);
        },
        1};

    const Function Exp{
        "exp", [](std::span<const double> s)
        {
            return std::exp(s[0]);
        },
        1};

    const Function Log{
        "log", [](std::span<const double> s)
        {
            return std::log(s[0]);
        },
        1};

}