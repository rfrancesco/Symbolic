#pragma once

namespace Symbolic::Core
{

    class Node;
    class Value;
    class Symbol;
    class Negative;
    class Sum;
    class Product;
    class Division;
    class Power;
    class FunctionNode;

    class ASTVisitor
    {
    public:
        virtual void visitValue(const Value &) = 0;
        virtual void visitSymbol(const Symbol &) = 0;
        virtual void visitNegative(const Negative &) = 0;
        virtual void visitSum(const Sum &) = 0;
        virtual void visitProduct(const Product &) = 0;
        virtual void visitDivision(const Division &) = 0;
        virtual void visitPower(const Power &) = 0;
        virtual void visitFunctionNode(const FunctionNode &) = 0;

        virtual ~ASTVisitor() = default;
    };
}