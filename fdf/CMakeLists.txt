cmake_minimum_required(VERSION 3.14)
project(fdf C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(fdf
        fdf.c
        fdf.h)
