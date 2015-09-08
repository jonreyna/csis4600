cmake_minimum_required(VERSION 3.3)
project(FanWait)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.c restart/restart.c)
add_executable(FanWait ${SOURCE_FILES})