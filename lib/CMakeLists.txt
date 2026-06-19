add_library(SymbolicCore
    src/Core/AbstractStructure/Expression.cpp
    src/Core/AbstractStructure/SymbolContext.cpp
    src/Core/ArithmeticalOperations/Sum.cpp
    src/Core/ArithmeticalOperations/Product.cpp
    src/Core/ArithmeticalOperations/Division.cpp
    src/Core/ArithmeticalOperations/Power.cpp
    # tutti i .cpp
)

# alias con namespace, convenzione moderna
add_library(Symbolic::Core ALIAS SymbolicCore)

target_include_directories(SymbolicCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(SymbolicCore PRIVATE -Wall -Wextra -Wpedantic)