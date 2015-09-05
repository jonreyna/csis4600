cmake_minimum_required(VERSION 3.2)
project(keeplog)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -Wall -Wextra")

set(SOURCE_FILES keeplog.c listlib.c listlib.h keeploglib.c keeploglib.h)
add_executable(keeplog ${SOURCE_FILES})