#pragma once

#include <string>
#include <span>
#include <functional>
#include <optional>
#include <stdexcept>

namespace Symbolic::Core
{
    class Function
    {
    private:
        std::string name_;
        std::optional<size_t> arity_;
        std::function<double(std::span<const double>)> impl;

    public:
        Function() = delete;
        Function(std::string name, std::function<double(std::span<const double>)> impl, std::optional<size_t> arity = std::nullopt) : name_(name), arity_(arity), impl(impl) {}

        std::string name() const
        {
            return name_;
        }

        std::optional<size_t> arity() const
        {
            return arity_;
        }

        double operator()(std::span<const double> args) const
        {
            if (arity_)
            {
                if (args.size() != *arity_)
                    throw std::invalid_argument("Function " + name_ + " called with wrong argument number");
            }
            return impl(args);
        }

        double operator()(std::initializer_list<double> args) const
        {
            if (arity_)
            {
                if (args.size() != *arity_)
                    throw std::invalid_argument("Function " + name_ + " called with wrong argument number");
            }
            return impl(std::span<const double>(args.begin(), args.end()));
        }
    };
}