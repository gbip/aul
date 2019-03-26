
flex_target(Lexer ${CMAKE_CURRENT_SOURCE_DIR}/lex.l
        ${CMAKE_CURRENT_SOURCE_DIR}/gen/lex.yy.c
        COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_SOURCE_DIR}/gen/lex.yy.h")

bison_target(Parser ${CMAKE_CURRENT_SOURCE_DIR}/syntax.y
        ${CMAKE_CURRENT_SOURCE_DIR}/gen/syntax.c
        COMPILE_FLAGS "-d")

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

set(SRC_COMPILER_LIBRARY
        co_ast.c
        co_symbol_table.c
        co_types.c
        co_ir.c
        ../virtual_machine/vm_op_code.c
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Lexer_OUTPUTS})

add_library(compiler STATIC ${SRC_COMPILER_LIBRARY})
add_library(compiler_test STATIC ${SRC_COMPILER_LIBRARY})
target_compile_definitions(compiler_test PRIVATE UNIT_TESTING)

set(SRC_FILES co_main.c)

add_executable(aul ${SRC_FILES})
target_link_libraries(aul compiler)

target_link_libraries(aul fl)

set(TEST_SRC_FILES
        co_ast.c
        co_symbol_table.c
        co_types.c
        co_tests.c)
