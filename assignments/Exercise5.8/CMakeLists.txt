cmake_minimum_required(VERSION 3.3)
project(Exercise5_8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g3")

set(SOURCE_FILES main.c)
add_executable(Exercise5_8 ${SOURCE_FILES})