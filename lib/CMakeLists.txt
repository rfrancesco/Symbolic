add_library(SymbolicCore
    src/Core/AST/Expression.cpp
    src/Core/AST/SymbolContext.cpp
    src/Core/Ops/Sum.cpp
    src/Core/Ops/Product.cpp
    src/Core/Ops/Division.cpp
    src/Core/Ops/Power.cpp
)

# alias con namespace, convenzione moderna
add_library(Symbolic::Core ALIAS SymbolicCore)

target_include_directories(SymbolicCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(SymbolicCore PRIVATE -Wall -Wextra -Wpedantic)