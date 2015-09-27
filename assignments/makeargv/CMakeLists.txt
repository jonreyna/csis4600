cmake_minimum_required(VERSION 2.4)
project(makeargv)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Og -Wall -Wextra")

set(SOURCE_FILES makeargv.c argtest.c)
add_executable(makeargv ${SOURCE_FILES})