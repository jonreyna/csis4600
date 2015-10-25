cmake_minimum_required(VERSION 2.4)
project(seqclientbad)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3 -Wall -O0")

set(SOURCE_FILES seqclientbad.c ../restart/restart.c)
add_executable(seqclientbad ${SOURCE_FILES})