// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/Core.hpp>
#include <Symbolic/Core/Algorithms/SimplifyTrivial.hpp>
#include <cmath>
#include <numeric>

using namespace Symbolic::Core;

TEST(Core_Algortithms_TrivialSimplify, SumZero)
{
    Expression expr;
    auto x = expr.makeSymbol("x");

    // clang-format off
    expr.root = expr.makeNode<Sum>({
        x,
        expr.makeNode<Value>(Rational{0}),
        expr.makeNode<Value>(Rational{1}),
        expr.makeNode<Value>(Rational{0})
    });
    // clang-format on

    Expression simple{simplifyTrivial(expr)};
    std::ostringstream os;
    simple.print(os);
    std::cout << os.str();
    EXPECT_EQ( os.str(), "(x)+(1)\n" );
}


TEST(Core_Algortithms_TrivialSimplify, ProductOne)
{
    Expression expr;
    auto x = expr.makeSymbol("x");

    // clang-format off
    expr.root = expr.makeNode<Product>({
        x,
        expr.makeNode<Value>(Rational{2}),
        expr.makeNode<Value>(Rational{1}),
        expr.makeNode<Value>(Rational{5})
    });
    // clang-format on

    Expression simple{simplifyTrivial(expr)};
    std::ostringstream os;
    simple.print(os);
    std::cout << os.str();
    EXPECT_EQ( os.str(), "(x)*(2)*(5)\n" );
}

TEST(Core_Algortithms_TrivialSimplify, ProductZero)
{
    Expression expr;
    auto x = expr.makeSymbol("x");

    // clang-format off
    expr.root = expr.makeNode<Product>({
        x,
        expr.makeNode<Value>(Rational{2}),
        expr.makeNode<Value>(Rational{0}),
        expr.makeNode<Value>(Rational{5})
    });
    // clang-format on

    Expression simple{simplifyTrivial(expr)};
    ASTDebugInfo d{simple.root};
    std::ostringstream os;
    simple.print(os);
    std::cout << os.str();
    EXPECT_EQ( os.str(), "0\n" );
}

TEST(Core_Algortithms_TrivialSimplify, DoubleNegative)
{
    Expression expr;
    auto x = expr.makeSymbol("x");

    // clang-format off
    expr.root = expr.makeNode<Product>({
        x,
        expr.makeNode<Negative>(expr.makeNode<Negative>(x))
    });
    // clang-format on

    Expression simple{simplifyTrivial(expr)};
    std::ostringstream os;
    simple.print(os);
    std::cout << os.str();
    EXPECT_EQ( os.str(), "(x)*(x)\n" );
}


