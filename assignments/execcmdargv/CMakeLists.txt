cmake_minimum_required(VERSION 3.3)
project(execcmdargv)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g3")

set(SOURCE_FILES main.c ../restart/restart.c ../makeargv/makeargv.c)
add_executable(execcmdargv ${SOURCE_FILES})