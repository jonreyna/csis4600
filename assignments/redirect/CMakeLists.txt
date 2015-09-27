cmake_minimum_required(VERSION 3.3)
project(redirect)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES redirect.c ../restart/restart.c)
add_executable(redirect ${SOURCE_FILES})