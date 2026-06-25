// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/Core.hpp>
#include <ostream>

using namespace Symbolic::Core;

// Checks that the copy has the same structure
// Check is performed by comparing structure print strings
TEST(Core_Algorithms_DeepCopy, StructureIsCopied)
{
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

    Expression copy{deepCopy(expr)};

    std::ostringstream o1, o2;
    expr.print(o1);
    expr.print(o2);
    EXPECT_EQ(o1.str(), o2.str());
}

// Checks that the expression and its copy do not share memory
// Nodes must live on different memory addresses
TEST(Core_Algorithms_DeepCopy, MemoryIsCopiedAndNotReused)
{
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

    Expression copy{deepCopy(expr)};

    ASTDebugInfo debug1{expr.root};
    ASTDebugInfo debug2{copy.root};

    auto memory1 = debug1.memory();
    auto memory2 = debug2.memory();

    ASSERT_EQ(memory1.size(), memory2.size());
    for (int i = 0; i < memory1.size(); i++)
    {
        EXPECT_NE(memory1[i], memory2[i]);
    }
}