# Dependencies
## Boost rational
find_package(Boost CONFIG REQUIRED)

# Define library
add_library(SymbolicCore
    src/Core/AST/Expression.cpp
    src/Core/AST/SymbolContext.cpp
    src/Core/Ops/Sum.cpp
    src/Core/Ops/Product.cpp
    src/Core/Ops/Division.cpp
    src/Core/Ops/Power.cpp
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