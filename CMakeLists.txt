cmake_minimum_required(VERSION 3.13)
project(aul C)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

find_package(FLEX)
find_package(BISON)
flex_target(Lexer ${CMAKE_CURRENT_BINARY_DIR}/../src/compiler/lex.l
        ${CMAKE_CURRENT_BINARY_DIR}/../src/compiler/lex.yy.c
        COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_BINARY_DIR}/../src/lex.yy.h")

bison_target(Parser ${CMAKE_CURRENT_BINARY_DIR}/../src/compiler/syntax.y
        ${CMAKE_CURRENT_BINARY_DIR}/../src/compiler/syntax.c
        COMPILE_FLAGS "-d")

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

set(SRC_FILES src/compiler/main.c ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS}
        src/compiler/ast.c
        src/compiler/symbol_table.c src/compiler/types.h src/compiler/types.c src/compiler/ir.c src/compiler/ir.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)
add_executable(aul ${SRC_FILES})
target_link_libraries(aul fl)


set(TEST_SRC_FILES
        src/compiler/ast.c
        src/compiler/symbol_table.c
        src/compiler/types.c
        src/tests.c)
add_executable(test_ast  ${TEST_SRC_FILES})