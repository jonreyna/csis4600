cmake_minimum_required(VERSION 2.4)
project(redirect)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g3")

set(SOURCE_FILES redirect.c ../restart/restart.c)
add_executable(redirect ${SOURCE_FILES})
