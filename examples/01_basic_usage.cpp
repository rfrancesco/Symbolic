#include <iostream>
#include <cmath>

#include "Symbolic/Core/Core.hpp"
#include "Symbolic/Core/Algorithms/Evaluator.hpp"

using namespace Symbolic::Core;
namespace Functions = Symbolic::Core::Functions;

int main()
{
    // Construct Expr(x,y) = -x + y^(1/2) + sin(z)
    Expression expr;
    auto x = expr.makeSymbol("x");
    auto y = expr.makeSymbol("y");
    auto z = expr.makeSymbol("z");

    // Define a function
    auto sum = expr.makeNode<Sum>({
            expr.makeNode<Negative>(x), expr.makeNode<Power>(y, expr.makeNode<Value>(Rational{1,2})),
            expr.makeFunctionNode(Functions::Sin,{z})});
    expr.root = sum;

    // Print expression
    std::cout << expr << "\n";

    // Evaluate the expression on (x, y) = (1.57, 3.0)
    SymbolContext ctx = {{"x", 1.57}, {"y", 3.0}, {"z", 1.0}};
    std::cout << ctx << "\n";
    std::cout << expr.evaluate(ctx) << std::endl;
    std::cout << Evaluator(expr)(ctx) << std::endl;

    // Another one!
    Expression expr2;
    x = expr2.makeSymbol("x");
    expr2.root = expr2.makeFunctionNode(Functions::Log, {expr2.makeFunctionNode(Functions::Exp, {x})});
    // Print expression
    std::cout << expr2 << "\n";

    // Evaluate the expression on x = 1.57
    SymbolContext ctx2 = {{"x", 1.57}};
    std::cout << ctx2 << "\n";
    std::cout << expr2.evaluate(ctx2) << std::endl;
    std::cout << Evaluator(expr2)(ctx2) << std::endl;
}
