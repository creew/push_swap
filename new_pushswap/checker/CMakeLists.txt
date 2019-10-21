cmake_minimum_required(VERSION 3.14)
project(checker C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        ./../libft
        ./../common)

add_executable(checker
        checker.c
        checker.h)
