#include <iostream>
#include <cmath>
#include <algorithm>

#include "Symbolic/Core/Core.hpp"

using namespace Symbolic::Core;

int main()
{
    // Construct Expr(x,y,z) = max(x,y,z+1)
    Expression expr;
    auto x = expr.makeSymbol("x");
    auto y = expr.makeSymbol("y");
    auto z = expr.makeSymbol("z");

    Function max{"max",std::ranges::max};

    auto result = expr.makeFunctionNode(max,{x,y,expr.makeNode<Sum>({z,expr.makeNode<Value>(Rational{1})})});
    expr.root = result;

    // Print expression
    std::cout << expr << "\n";

    // Evaluate the expression on (x, y) = (1.57, 3.0)
    SymbolContext ctx = {{"x", 1.57}, {"y", 3.0}, {"z", 25.0}};
    std::cout << ctx << "\n";
    std::cout << Evaluator{expr}(ctx) << std::endl;


}
