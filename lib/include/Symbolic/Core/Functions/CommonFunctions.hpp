#pragma once

#include <span>
#include <cmath>
#include "Symbolic/Core/Functions/Function.hpp"

namespace Symbolic::Core::Functions
{
    inline Function Sin()
    {
        return Function{
            "sin", [](std::span<const double> s)
            {
                return std::sin(s[0]);
            },
            1};
    }

    inline Function Cos()
    {
        return Function{
            "cos", [](std::span<const double> s)
            {
                return std::cos(s[0]);
            },
            1};
    }

    inline Function Tan()
    {
        return Function{
            "tan", [](std::span<const double> s)
            {
                return std::tan(s[0]);
            },
            1};
    }

    inline Function Exp()
    {
        return Function{
            "exp", [](std::span<const double> s)
            {
                return std::exp(s[0]);
            },
            1};
    }

    inline Function Log()
    {
        return Function{
            "log", [](std::span<const double> s)
            {
                return std::log(s[0]);
            },
            1};
    }
}