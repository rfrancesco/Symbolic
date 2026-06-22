// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/Core.hpp>
#include <cmath>

using namespace Symbolic::Core;

static double f1(double x, double y, double z)
{
    return -x + std::pow(y, 1.0 / 2) + std::sin(z) + 3. / 2;
}

TEST(Core_MathCorrectness, Eq1)
{

    // f1(x,y,z) = -x + y^{1/2} + sin(z) + 3/2
    Expression expr;
    auto x = expr.makeSymbol("x");
    auto y = expr.makeSymbol("y");
    auto z = expr.makeSymbol("z");

    // Define a function
    expr.root = expr.makeNode<Sum>({expr.makeNode<Negative>(x), expr.makeNode<Power>(y, expr.makeNode<Value>(Rational{1, 2})),
                                    expr.makeFunctionNode(Functions::Sin, {z}),
                                    expr.makeNode<Value>(Rational{3, 2})});

    // Evaluate the expression on (x, y) = (1.57, 3.0)

    double vx, vy, vz;
    SymbolContext ctx{};

    vx = 1.57;
    vy = 3.0;
    vz = 1.0;
    ctx = {{"x", vx}, {"y", vy}, {"z", vz}};
    ASSERT_DOUBLE_EQ(f1(vx, vy, vz), expr.evaluate(ctx));

    vx = 3.1826364;
    vy = 2.1827832;
    vz = -1.0;
    ctx = {{"x", vx}, {"y", vy}, {"z", vz}};
    ASSERT_DOUBLE_EQ(f1(vx, vy, vz), expr.evaluate(ctx));
}
