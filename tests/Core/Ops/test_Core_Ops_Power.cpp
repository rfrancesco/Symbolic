// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <cmath>
#include <Symbolic/Core/AST/Value.hpp>
#include <Symbolic/Core/AST/Symbol.hpp>
#include <Symbolic/Core/Ops/Power.hpp>

using namespace Symbolic::Core;

TEST(Core_AST_Power, Evaluate)
{
    Rational r{3, 5}, s{5,8};
    Value a{r}, b{s};
    Power pow{&a, &b};
    EXPECT_DOUBLE_EQ(pow.evaluate(SymbolContext{}), std::pow(toDouble(r), toDouble(s)));
}