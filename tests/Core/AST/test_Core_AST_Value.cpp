// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/AST/Value.hpp>

using namespace Symbolic::Core;

TEST(Core_AST_Value, GetValue)
{
    Rational r{3, 5};
    Value v{r};
    EXPECT_EQ(v.value(), r);
}

TEST(Core_AST_Value, PrintLargeDenominatorsAsFloat)
{
    Value v{Rational{12345, 10000}};
    std::ostringstream out;
    v.print(out);
    EXPECT_EQ(out.str(), "1.2345");
}

TEST(Core_AST_Value, PrintSmallDenominatorsAsFractions)
{
    Value v{Rational{3, 5}};
    std::ostringstream out;
    v.print(out);
    EXPECT_EQ(out.str(), "3/5");
}

TEST(Core_AST_Value, Evaluate)
{
    Rational r{3, 5};
    Value v{r};
    EXPECT_EQ(v.evaluate(SymbolContext{}), toDouble(r));
}