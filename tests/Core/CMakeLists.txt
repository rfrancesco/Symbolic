add_subdirectory(AST)
add_subdirectory(Ops)
add_subdirectory(Algorithms)

target_sources(tests PRIVATE
    test_Core_MathCorrectness.cpp
)