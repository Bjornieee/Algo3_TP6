cmake_minimum_required(VERSION 3.26)
project(base_code_lab6 C)

set(CMAKE_C_STANDARD 11)

include_directories(Code)

add_executable(base_code_lab6
        Code/bstree.c
        Code/bstree.h
        Code/main.c
        Code/queue.c
        Code/queue.h)
