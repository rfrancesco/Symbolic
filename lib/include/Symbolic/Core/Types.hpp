#pragma once

#include <string>
#include <unordered_map>
#include <ostream>
#include <boost/rational.hpp>

namespace Symbolic::Core
{
    using Rational = boost::rational<int64_t>;

    inline bool hasFiniteRepresentation(int n)
    {
        if (n <= 0)
            return false;
        while (n % 2 == 0)
            n /= 2;
        while (n % 5 == 0)
            n /= 5;
        return n == 1;
    }

    inline double toDouble(const Rational &r) { return boost::rational_cast<double>(r); }

    inline void printRational(std::ostream &os, const Rational &r)
    {
        if (r.denominator() == 1)
            os << r.numerator();
        else if (r.denominator() > 10 && hasFiniteRepresentation(r.denominator()))
        {
            os << boost::rational_cast<double>(r);
        }
        else
            os << r;
    }

    using SymbolName = std::string;
    using SymbolContext = std::unordered_map<SymbolName, double>;
}