add_executable(tests)
target_link_libraries(tests PRIVATE GTest::gtest_main Symbolic::Core)

add_subdirectory(Core)

include(GoogleTest)
gtest_discover_tests(tests)