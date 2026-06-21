// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <cmath>
#include <Symbolic/Core/AST/Value.hpp>
#include <Symbolic/Core/AST/Symbol.hpp>
#include <Symbolic/Core/Ops/Negative.hpp>

using namespace Symbolic::Core;

TEST(Core_AST_Negative, Evaluate)
{
    Rational r{3, 5};
    Value a{r};
    Negative res{&a};
    EXPECT_DOUBLE_EQ(res.evaluate(SymbolContext{}), toDouble(-r));
    EXPECT_DOUBLE_EQ(res.evaluate(SymbolContext{}), -(a.evaluate(SymbolContext{})));
}