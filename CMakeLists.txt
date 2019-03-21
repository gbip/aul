cmake_minimum_required(VERSION 3.13)
project(aul C)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

find_package(FLEX)
find_package(BISON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")


find_package(CMocka CONFIG REQUIRED)
include(AddCMockaTest)
include(AddMockedTest)
add_subdirectory(tests)
enable_testing()

add_subdirectory(src)