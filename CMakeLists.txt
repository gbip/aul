cmake_minimum_required(VERSION 3.13)
project(aul C)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

find_package(FLEX)
find_package(BISON)

add_subdirectory(src)