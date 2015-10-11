cmake_minimum_required(VERSION 2.4)
project(Exercise5_8)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3 -fsanitize=address -fno-omit-frame-pointer -fsanitize-memory-track-origins=2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3")

set(SOURCE_FILES main.c file_perms.c)
add_executable(Exercise5_8 ${SOURCE_FILES})
