add_subdirectory(AST)
add_subdirectory(Ops)

target_sources(tests PRIVATE
    test_Core_MathCorrectness.cpp
)