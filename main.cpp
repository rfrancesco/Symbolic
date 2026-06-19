#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

#include "Symbolic/Core/Core.hpp"

using namespace Symbolic::Core;

/* This main is a test environment, and it is very ugly. 
   Still WIP!!!*/

int main(int, char**){
    std::cout << "Hello, from Symbolic!\n";

    Expression e;
    Sum* plus = e.makeNode<Sum>();
    e.tree = plus;
    // std::cout << e.tree->evaluate(SymbolContext()) << std::endl;
    plus->addChild(e.makeNode<Value>(1.0));
    plus->addChild(e.makeNode<Negative>(e.makeNode<Value>(0.5)));
    // plus->addChild(e.makeNode<Negative>(nullptr));

    // std::cout << e.evaluate(SymbolContext()) << std::endl;
    // std::cout << e(SymbolContext()) << std::endl;
    Sum* nestedSum = e.makeNode<Sum>();
    plus->addChild(nestedSum);
    nestedSum->addChild(e.makeSymbol("x"));
    nestedSum->addChild(e.makeNode<Negative>(e.makeSymbol("y")));

    std::cout << e << std::endl;

    SymbolContext ctx {{"x", 2.0}, {"y", 1.0}};
    std::cout << ctx << std::endl;

    std::cout << e(ctx) << std::endl;
    // std::cout << e(SymbolContext{{"x", 10.0}}) << std::endl;
    // plus->addChild(e.getSymbol("x"));
    // std::cout << e(SymbolContext{{"x", 5.0}}) << std::endl;
    // std::cout << e(SymbolContext{{"x", 10.0}}) << std::endl;
    e.print(std::cout);
}
