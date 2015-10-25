cmake_minimum_required(VERSION 2.4)
project(pipeserver)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3 -Wall -O0")

set(SOURCE_FILES pipserver.c ../restart/restart.c)

add_executable(pipeserver ${SOURCE_FILES})
