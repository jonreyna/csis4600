cmake_minimum_required(VERSION 3.3)
project(makeargv)

set(CMAKE_C_FLAGS -std=c99)
set(CMAKE_C_COMPILER "clang")

set(SOURCE_FILES makeargv.c argtest.c)
add_executable(makeargv ${SOURCE_FILES})