# Dependencies
## Boost rational
find_package(Boost CONFIG REQUIRED)

# Define library
add_library(SymbolicCore
    src/Core/AST/Expression.cpp
    src/Core/AST/SymbolContext.cpp
    src/Core/AST/Nodes/Sum.cpp
    src/Core/AST/Nodes/Product.cpp
    src/Core/AST/Nodes/Division.cpp
    src/Core/AST/Nodes/Power.cpp
    src/Core/Algorithms/Evaluator.cpp
    src/Core/Algorithms/EvaluatorImpl.cpp
    src/Core/Algorithms/ASTDebugInfo.cpp
)

add_library(Symbolic::Core ALIAS SymbolicCore)

target_include_directories(SymbolicCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(SymbolicCore
    PUBLIC
    Boost::headers
)

target_compile_options(SymbolicCore PRIVATE -Wall -Wextra -Wpedantic)