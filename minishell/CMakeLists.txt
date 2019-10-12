cmake_minimum_required(VERSION 3.14)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(minishell
        minishell.c
        minishell.h)
