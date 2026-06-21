// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/AST/Symbol.hpp>

using namespace Symbolic::Core;

TEST(Core_AST_Symbol, GetName)
{
    std::string name = "x";
    Symbol x{name};
    EXPECT_EQ(name, x.name());
}

TEST(Core_AST_Symbol, Print)
{
    std::string name = "x";
    Symbol x{name};
    std::ostringstream os;
    x.print(os);
    EXPECT_EQ(name, os.str());
}

TEST(Core_AST_Symbol, Evaluate)
{
    std::string name = "x";
    Symbol x{name};
    double value = 1.23456789;
    EXPECT_DOUBLE_EQ(value, x.evaluate(SymbolContext{{name, value}}));
}

