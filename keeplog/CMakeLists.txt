cmake_minimum_required(VERSION 2.4)
project(keeplog)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Og -Wall -Wextra")

set(SOURCE_FILES keeplog.c listlib.c listlib.h keeploglib.c keeploglib.h)
add_executable(keeplog ${SOURCE_FILES})
