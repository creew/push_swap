cmake_minimum_required(VERSION 3.14)
project(fdf C)

set(CMAKE_C_STANDARD 11)

include_directories(. ./minilibx_macos ./libft)

add_executable(fdf
        fdf.c
        fdf.h)

find_library(FT ft ./libft)
find_library(MLX mlx ./minilibx_macos)
target_link_libraries(fdf PUBLIC ${FT} ${MLX} "-framework AppKit" "-framework OpenGL")
