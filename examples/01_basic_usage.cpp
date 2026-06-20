#include <iostream>
#include <cmath>

#include "Symbolic/Core/Core.hpp"

using namespace Symbolic::Core;

int main()
{
    // Construct Expr(x,y) = -x + y^(1/2) + sin(z)
    Expression expr;
    auto x = expr.makeSymbol("x");
    auto y = expr.makeSymbol("y");
    auto z = expr.makeSymbol("z");

    // Define a function (note: yes, I am working to make the interface less ugly)
    Function sin{"sin",1,1,[](std::span<const double> s) {
        return std::sin(s[0]);
    }};

    auto sum = expr.makeNode<Sum>({
            expr.makeNode<Negative>(x), expr.makeNode<Power>(y, expr.makeNode<Value>(Rational{1,2})),
            expr.makeFunctionNode(sin,{z})});
    expr.root = sum;

    // Print expression
    std::cout << expr << "\n";

    // Evaluate the expression on (x, y) = (1.57, 3.0)
    SymbolContext ctx = {{"x", 1.57}, {"y", 3.0}, {"z", 1.0}};
    std::cout << ctx << "\n";
    std::cout << expr.evaluate(ctx) << std::endl;


}
