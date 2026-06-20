#pragma once

#include <string>
#include <unordered_map>
#include <ostream>
#include <boost/rational.hpp>

namespace Symbolic::Core
{
    using Rational = boost::rational<int64_t>;

    inline bool isPowerOf10(int n)
    {
        if (n <= 0)
            return false;
        while (n % 10 == 0)
            n /= 10;
        return n == 1;
    }

    inline double toDouble(const Rational &r) { return boost::rational_cast<double>(r); }

    inline void printRational(std::ostream &os, const Rational &r)
    {
        if (r.denominator() == 1)
            os << r.numerator();
        else if (isPowerOf10(r.denominator()))
        {
            os << boost::rational_cast<double>(r);
        }
        else
            os << r;
    }

    using SymbolName = std::string;
    using SymbolContext = std::unordered_map<SymbolName, double>;
}