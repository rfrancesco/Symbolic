// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/AST/Value.hpp>
#include <Symbolic/Core/AST/Symbol.hpp>
#include <Symbolic/Core/Ops/Division.hpp>

using namespace Symbolic::Core;

TEST(Core_AST_Division, Evaluate)
{
    Rational r{3, 5}, s{5,8};
    Value a{r}, b{s};
    Division div{&a, &b};
    EXPECT_DOUBLE_EQ(div.evaluate(SymbolContext{}), toDouble(r/s));
}