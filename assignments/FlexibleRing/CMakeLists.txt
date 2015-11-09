cmake_minimum_required(VERSION 2.4)
project(FlexibleRing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp FlexibleRing.cpp FlexibleRing.h)
add_executable(FlexibleRing ${SOURCE_FILES})