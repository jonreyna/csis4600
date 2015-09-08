cmake_minimum_required(VERSION 3.3)
project(FanWaitMsg)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.c)
add_executable(FanWaitMsg ${SOURCE_FILES})