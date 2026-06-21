#pragma once

#include <string>
#include <span>
#include <functional>
#include <optional>

namespace Symbolic::Core
{
    class Function
    {
    private:
    public:
        std::string name;
        std::optional<size_t> arity;

        std::function<double(std::span<const double>)> impl;

        Function() = delete;
        Function(std::string name, std::function<double(std::span<const double>)> impl, std::optional<size_t> arity = std::nullopt) : name(name), impl(impl), arity(arity) {}

        double operator()(std::span<const double> args) const
        {
            if (arity)
            {
                if (args.size() != *arity)
                    throw std::invalid_argument("Function " + name + " called with wrong argument number");
            }
            return impl(args);
        }

        double operator()(std::initializer_list<double> args) const
        {
            if (arity)
            {
                if (args.size() != *arity)
                    throw std::invalid_argument("Function " + name + " called with wrong argument number");
            }
            return impl(std::span<const double>(args.begin(), args.end()));
        }
    };
}