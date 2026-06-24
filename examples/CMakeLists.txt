set(EXAMPLES 01_basic_usage
    02_user_defined_functions
    03_AST_debugging)

foreach(EXAMPLE ${EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    target_link_libraries(${EXAMPLE} PRIVATE Symbolic::Core)
endforeach()