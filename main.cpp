#include <iostream>
#include <cmath>

#include "Symbolic/Core/Core.hpp"

using namespace Symbolic::Core;

/* This main is a test environment, and it is very ugly. 
   Still WIP!!!*/

int main(int, char**){
    std::cout << "Hello, from Symbolic!\n";

    Expression e;
    Sum* plus = e.makeNode<Sum>();
    // e.tree = plus;
    // std::cout << e.tree->evaluate(SymbolContext()) << std::endl;
    plus->addChild(e.makeNode<Value>(1.0));
    plus->addChild(e.makeNode<Negative>(e.makeNode<Value>(0.5)));
    // plus->addChild(e.makeNode<Negative>(nullptr));

    // std::cout << e.evaluate(SymbolContext()) << std::endl;
    // std::cout << e(SymbolContext()) << std::endl;
    Sum* nestedSum = e.makeNode<Sum>();
    plus->addChild(nestedSum);
    nestedSum->addChild(e.makeSymbol("x"));
    Product* nestedProd = e.makeNode<Product>();
    nestedProd->makeChild<Value>(e,0.5);
    nestedProd->addChild(e.makeNode<Negative>(e.makeSymbol("y")));
    nestedSum->addChild(nestedProd);

    Power* pow = e.makeNode<Power>(e.getSymbol("x"),e.makeNode<Value>(0.5));
    Division* division = e.makeNode<Division>(plus, pow);
    e.tree = division;

    std::cout << e << std::endl;

    double x = 1.2345;
    double y = 3.14159;

    SymbolContext ctx {{"x", x}, {"y", y}};
    std::cout << ctx << std::endl;
    std::cout << e(ctx) << std::endl;

    std::cout << "Cfr: " << ((1-0.5)+(x+(0.5*(-y))))/std::sqrt(x) << std::endl;
    // std::cout << e(SymbolContext{{"x", 10.0}}) << std::endl;
    // plus->addChild(e.getSymbol("x"));
    // std::cout << e(SymbolContext{{"x", 5.0}}) << std::endl;
    // std::cout << e(SymbolContext{{"x", 10.0}}) << std::endl;
    e.print(std::cout);
}
