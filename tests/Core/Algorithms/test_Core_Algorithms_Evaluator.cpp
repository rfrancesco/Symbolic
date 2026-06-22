// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/Core.hpp>
#include <cmath>

using namespace Symbolic::Core;

static double f1(double x, double y, double z)
{
    return -x + std::pow(y, 1.0 / 2) + std::sin(z) + 3. / 2;
}

static double f2(double x, double y)
{
    return x + std::cos(x * (y + 1) + y * std::sin(x)) + x / y;
}

TEST(Core_Algorithms_Evaluator, Eq1)
{
    // Tests: Sum, Negative, Power, Value, Symbol, FunctionNode
    // f1(x,y,z) = -x + y^{1/2} + sin(z) + 3/2
    Expression expr;
    auto x = expr.makeSymbol("x");
    auto y = expr.makeSymbol("y");
    auto z = expr.makeSymbol("z");

    // clang-format off
    expr.root = expr.makeNode<Sum>({
        expr.makeNode<Negative>(x), 
        expr.makeNode<Power>(
            y, 
            expr.makeNode<Value>(Rational{1, 2})
        ),
        expr.makeFunctionNode(Functions::Sin, {z}),
        expr.makeNode<Value>(Rational{3, 2})
    });
    // clang-format on
   
    double vx, vy, vz;
    SymbolContext ctx{};
    Evaluator eval{expr};

    vx = 1.57;
    vy = 3.0;
    vz = 1.0;
    ctx = {{"x", vx}, {"y", vy}, {"z", vz}};
    ASSERT_DOUBLE_EQ(f1(vx, vy, vz), eval(ctx));

    vx = 3.1826364;
    vy = 2.1827832;
    vz = -1.0;
    ctx = {{"x", vx}, {"y", vy}, {"z", vz}};
    ASSERT_DOUBLE_EQ(f1(vx, vy, vz), eval(ctx));
}

TEST(Core_Algorithms_Evaluator, Eq2)
{
    // Tests: Sum, Product, FunctionNode, Symbol, Value, Division
    // f2(x,y) = x + cos(x * (y+1) + y * sin(x)) + x/y
    Expression expr;
    auto x = expr.makeSymbol("x");
    auto y = expr.makeSymbol("y");

    // clang-format off
    expr.root = expr.makeNode<Sum>({
        x,
        expr.makeFunctionNode(Functions::Cos, {
            expr.makeNode<Sum>({
                expr.makeNode<Product>({
                    x,
                    expr.makeNode<Sum>({
                        y, 
                        expr.makeNode<Value>(Rational{1})
                    })
                }),
                expr.makeNode<Product>({
                    y,
                    expr.makeFunctionNode(Functions::Sin, {x})
                })
            })
        }),
        expr.makeNode<Division>(x, y)
    });
    // clang-format on

    double vx, vy, vz;
    SymbolContext ctx{};
    Evaluator eval{expr};

    vx = 1.234567;
    vy = 0.123456;
    ctx = {{"x", vx}, {"y", vy}};
    ASSERT_DOUBLE_EQ(f2(vx, vy), eval(ctx));

    vx = -1.234567;
    vy = 3.123456;
    ctx = {{"x", vx}, {"y", vy}};
    ASSERT_DOUBLE_EQ(f2(vx, vy), eval(ctx));

    vx = 31234.434312;
    vy = -41.1323456;
    ctx = {{"x", vx}, {"y", vy}};
    ASSERT_DOUBLE_EQ(f2(vx, vy), eval(ctx));
}
