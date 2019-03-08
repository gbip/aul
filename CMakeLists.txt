cmake_minimum_required(VERSION 3.13)
project(aul C)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
FIND_PROGRAM(FLEX_EXECUTABLE NAMES flex flex.exe )

IF(FLEX_EXECUTABLE)
    SET(FLEX_FOUND TRUE)

    EXECUTE_PROCESS(COMMAND ${FLEX_EXECUTABLE} --version
            OUTPUT_VARIABLE _FLEX_VERSION
            )
    string (REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" FLEX_VERSION
            "${_FLEX_VERSION}")
ENDIF(FLEX_EXECUTABLE)

IF(FLEX_FOUND)
    IF(NOT Flex_FIND_QUIETLY)
        MESSAGE(STATUS "Found Flex: ${FLEX_EXECUTABLE}")
    ENDIF(NOT Flex_FIND_QUIETLY)
ELSE(FLEX_FOUND)
    IF(Flex_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find Flex")
    ENDIF(Flex_FIND_REQUIRED)
ENDIF(FLEX_FOUND)

add_custom_target("run_lex")
ADD_CUSTOM_COMMAND(
        COMMAND ${FLEX_EXECUTABLE}
        ARGS -o "${CMAKE_CURRENT_SOURCE_DIR}/src/lex.yy.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/lex.l"
        TARGET run_lex
        OUTPUTS "src/lex.yy.c"
)

add_executable(aul src/main.c)
add_dependencies(aul run_lex)

add_executable(lex src/lex.yy.c)
add_dependencies(lex run_lex)
