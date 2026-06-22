#pragma once

#include <span>
#include <cmath>
#include "Symbolic/Core/Functions/Function.hpp"

namespace Symbolic::Core::Functions
{
    inline const Function Sin{
        "sin", [](std::span<const double> s)
        {
            return std::sin(s[0]);
        },
        1};

    inline const Function Cos{
        "cos", [](std::span<const double> s)
        {
            return std::cos(s[0]);
        },
        1};

    inline const Function Tan{
        "tan", [](std::span<const double> s)
        {
            return std::tan(s[0]);
        },
        1};

    inline const Function Exp{
        "exp", [](std::span<const double> s)
        {
            return std::exp(s[0]);
        },
        1};

    inline Function Log{
        "log", [](std::span<const double> s)
        {
            return std::log(s[0]);
        },
        1};

}