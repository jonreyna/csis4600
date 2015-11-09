cmake_minimum_required(VERSION 2.4)
project(ring)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3 -Wall -Wextra")

set(SOURCE_FILES ring.c)
add_executable(ring ${SOURCE_FILES})
