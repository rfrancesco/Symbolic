// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/AST/Value.hpp>
#include <Symbolic/Core/AST/Symbol.hpp>
#include <Symbolic/Core/Ops/Product.hpp>

using namespace Symbolic::Core;

TEST(Core_AST_Product, Evaluate)
{
    Rational r{3, 5}, s{5,8}, t{2};
    Value a{r}, b{s}, c{t};
    Symbol x{"x"}, y{"y"};
    double xval = 1.234567, yval = 3.14159;
    Product prod{&a, &b, &c, &x, &y};
    EXPECT_DOUBLE_EQ(prod.evaluate(SymbolContext{{"x", xval}, {"y", yval}}), toDouble(r*s*t)*xval*yval);
}