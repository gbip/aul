
flex_target(Lexer ${CMAKE_CURRENT_SOURCE_DIR}/lex.l
        ${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.c
        COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.h")

bison_target(Parser ${CMAKE_CURRENT_SOURCE_DIR}/syntax.y
        ${CMAKE_CURRENT_SOURCE_DIR}/syntax.c
        COMPILE_FLAGS "-d")

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

set(SRC_FILES ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS}
        main.c
        ast.c
        symbol_table.c
        types.c
        ir.c
        ir.h)

add_executable(aul ${SRC_FILES})

target_link_libraries(aul fl)

set(TEST_SRC_FILES
        ast.c
        symbol_table.c
        types.c
        tests.c)
add_executable(test_ast  ${TEST_SRC_FILES})