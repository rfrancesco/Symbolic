#include <iostream>
#include <cmath>

#include "Symbolic/Core/Core.hpp"

using namespace Symbolic::Core;

int main()
{
    // Construct Expr(x,y) = -x + y^(1/2)
    Expression expr;
    auto x = expr.makeSymbol("x");
    auto y = expr.makeSymbol("y");

    auto sum = expr.makeNode<Sum>({expr.makeNode<Negative>(x), expr.makeNode<Power>(y, expr.makeNode<Value>(Rational{1,2}))});
    expr.root = sum;

    // Print expression
    std::cout << expr << "\n";

    // Evaluate the expression on (x, y) = (1.57, 3.0)
    SymbolContext ctx = {{"x", 1.57}, {"y", 3.0}};
    std::cout << ctx << "\n";
    std::cout << expr.evaluate(ctx) << std::endl;
}
