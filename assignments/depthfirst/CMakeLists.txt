cmake_minimum_required(VERSION 2.4)
project(depthfirst)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3")

set(SOURCE_FILES depthfirst.c file_perms.c)
add_executable(depthfirst ${SOURCE_FILES})
