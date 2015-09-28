cmake_minimum_required(VERSION 2.4)
project(runback)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g3")

set(SOURCE_FILES runback.c ../restart/restart.c ../makeargv/makeargv.c)
add_executable(runback ${SOURCE_FILES})