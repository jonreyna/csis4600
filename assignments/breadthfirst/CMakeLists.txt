cmake_minimum_required(VERSION 2.4)
project(breadthfirst)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ggdb3")

set(SOURCE_FILES breadthfirst.cpp file_perms.c)
add_executable(breadthfirst ${SOURCE_FILES})
