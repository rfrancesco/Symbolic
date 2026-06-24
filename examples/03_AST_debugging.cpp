#include <iostream>
#include <cmath>

#include "Symbolic/Core/Core.hpp"

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
    Evaluator eval{expr};
    std::cout << eval(ctx) << std::endl;

    ASTDebugInfo(expr.root);
}
