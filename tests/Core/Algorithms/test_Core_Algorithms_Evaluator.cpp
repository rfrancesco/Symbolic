// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/Core.hpp>
#include <cmath>
#include <numeric>

using namespace Symbolic::Core;

static double f1(double x, double y, double z)
{
    return -x + std::pow(y, 1.0 / 2) + std::sin(z) + 3. / 2;
}

static double f2(double x, double y)
{
    return x + std::cos(x * (y + 1) + y * std::sin(x)) + x / y;
}

TEST(Core_Algorithms_Evaluator, ValueEval)
{
    Expression expr;
    Rational r{5, 4};
    expr.root = expr.makeNode<Value>(r);
    Evaluator eval{expr};

    ASSERT_DOUBLE_EQ(toDouble(r), eval(SymbolContext{}));
}

TEST(Core_Algorithms_Evaluator, SymbolEval)
{
    Expression expr;
    expr.root = expr.makeNode<Symbol>("x");
    Evaluator eval{expr};

    double x;
    SymbolContext ctx;

    x = 1.23456;
    ctx = {{"x", x}};
    ASSERT_DOUBLE_EQ(x, eval(ctx));

    x = 3.14159;
    ctx = {{"x", x}};
    ASSERT_DOUBLE_EQ(x, eval(ctx));
}

TEST(Core_Algorithms_Evaluator, SymbolExceptions)
{
    Expression expr;
    expr.root = expr.makeNode<Symbol>("x");
    
    Evaluator eval{expr};

    double x;
    SymbolContext ctx;

    ASSERT_NO_THROW(eval(SymbolContext{{"x", 1.2345}}));
    ASSERT_NO_THROW(eval(SymbolContext{{"x", 1.2345}, {"y", 2.34567}}));
    ASSERT_ANY_THROW(eval(SymbolContext{{"y", 2.34567}}));
}

TEST(Core_Algorithms_Evaluator, NegativeEval)
{
    Expression expr;
    Rational r{5, 4};

    // clang-format off
    expr.root = expr.makeNode<Negative>(
        expr.makeNode<Value>(r)
    );
    // clang-format on

    Evaluator eval{expr};
    
    ASSERT_DOUBLE_EQ(toDouble(-r), eval(SymbolContext{}));
}

TEST(Core_Algorithms_Evaluator, SumEval)
{
    Expression expr;
    Rational r{5, 4}, s{3, 2};

    // clang-format off
    expr.root = expr.makeNode<Sum>({
        expr.makeNode<Value>(r),
        expr.makeNode<Value>(s)
    });
    // clang-format on

    Evaluator eval{expr};

    ASSERT_DOUBLE_EQ(toDouble(r + s), eval(SymbolContext{}));
}

TEST(Core_Algorithms_Evaluator, ProductEval)
{
    Expression expr;
    Rational r{5, 4}, s{3, 2};

    // clang-format off
    expr.root = expr.makeNode<Product>({
        expr.makeNode<Value>(r),
        expr.makeNode<Value>(s)
    });
    // clang-format on

    Evaluator eval{expr};

    ASSERT_DOUBLE_EQ(toDouble(r * s), eval(SymbolContext{}));
}

TEST(Core_Algorithms_Evaluator, DivisionEval)
{
    Expression expr;
    Rational r{5, 4}, s{3, 2};

    // clang-format off
    expr.root = expr.makeNode<Division>(
        expr.makeNode<Value>(r),
        expr.makeNode<Value>(s)
    );
    // clang-format on

    Evaluator eval{expr};

    ASSERT_DOUBLE_EQ(toDouble(r / s), eval(SymbolContext{}));
}

TEST(Core_Algorithms_Evaluator, PowerEval)
{
    Expression expr;
    Rational r{5, 4}, s{3, 2};

    // clang-format off
    expr.root = expr.makeNode<Power>(
        expr.makeNode<Value>(r),
        expr.makeNode<Value>(s)
    );
    // clang-format on

    Evaluator eval{expr};

    ASSERT_DOUBLE_EQ(std::pow(toDouble(r), toDouble(s)), eval(SymbolContext{}));
}

TEST(Core_Algorithms_Evaluator, FunctionNodeUnaryEval)
{
    Expression expr;
    Rational r{5, 4};

    // clang-format off
    expr.root = expr.makeFunctionNode(
        Functions::Tan,
        {expr.makeNode<Value>(r)}
    );
    // clang-format on

    Evaluator eval{expr};

    ASSERT_DOUBLE_EQ(std::tan(toDouble(r)), eval(SymbolContext{}));
}

TEST(Core_Algorithms_Evaluator, FunctionNodeBinaryEval)
{
    Expression expr;
    Rational r{5, 4}, s{3, 2};

    // clang-format off
    Function f{
        "f",
        [](std::span<const double> v) { return std::sin(v[0] + v[1]); },
        2
    };
    // clang-format on

    // clang-format off
    expr.root = expr.makeFunctionNode(
        f,
        {
            expr.makeNode<Value>(r),
            expr.makeNode<Value>(s)
        }
    );
    // clang-format on

    Evaluator eval{expr};

    ASSERT_DOUBLE_EQ(std::sin(toDouble(r + s)), eval(SymbolContext{}));
}

TEST(Core_Algorithms_Evaluator, FunctionNodeNaryEval)
{
    Expression expr;
    Rational r{5, 4}, s{3, 2}, t{1, 5}, u{2, 25};

    // clang-format off
    Function f{
        "f",
        [](std::span<const double> v) { return std::sin(std::accumulate(v.begin(), v.end(), 0.0)); }
    };
    // clang-format on

    // clang-format off
    expr.root = expr.makeFunctionNode(
        f,
        {
            expr.makeNode<Value>(r),
            expr.makeNode<Value>(s),
            expr.makeNode<Value>(t),
            expr.makeNode<Value>(u)
        }
    );
    // clang-format on

    Evaluator eval{expr};
    double sum = 0.0;
    sum += toDouble(r);
    sum += toDouble(s);
    sum += toDouble(t);
    sum += toDouble(u);

    ASSERT_DOUBLE_EQ(std::sin(sum), eval(SymbolContext{}));
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
