// tests/Core/Fixture.hpp
#include <gtest/gtest.h>
#include <Symbolic/Core/AST/Value.hpp>

using namespace Symbolic::Core;

TEST(Core_AST_Value,Evaluate) {
    Value v { 1.0 };
    SymbolContext ctx {};
    EXPECT_DOUBLE_EQ(v.evaluate(ctx), 1.0);
}

TEST(Core_AST_Value,Print) {
    Value v { 1.2345 };
    std::ostringstream out;
    v.print(out);
    EXPECT_EQ(out.str(), "1.2345");
}