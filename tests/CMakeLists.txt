set(TEST_AST_SOURCES ../src/compiler/co_ast.c)

include_directories(../src/compiler)

add_compile_definitions(UNIT_TESTING)
add_mocked_test(co ${TEST_SOURCES} LINK_LIBRARIES compiler_test)