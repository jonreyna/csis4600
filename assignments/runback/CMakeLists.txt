cmake_minimum_required(VERSION 3.3)
project(runback)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES runback.c ../restart/restart.c ../makeargv/makeargv.c)
add_executable(runback ${SOURCE_FILES})