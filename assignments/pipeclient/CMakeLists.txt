cmake_minimum_required(VERSION 2.4)
project(pipeclient)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3 -Wall -O0")

set(SOURCE_FILES pipeclient.c ../restart/restart.c)
add_executable(pipeclient ${SOURCE_FILES})