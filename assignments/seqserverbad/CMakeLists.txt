cmake_minimum_required(VERSION 2.4)
project(seqserverbad)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3 -O0 -Wall")

set(SOURCE_FILES sqserverbad.c ../restart/restart.c)
add_executable(seqserverbad ${SOURCE_FILES})