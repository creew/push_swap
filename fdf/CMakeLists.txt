cmake_minimum_required(VERSION 3.14)
project(fdf C)

set(CMAKE_C_STANDARD 11)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

add_executable(fdf
        fdf.c
        fdf.h read_map.c draw_main.c init_images.c
        mouse_moves.c getters.c transforms.c draw_line.c mouse_hook.c key_hook.c colorize_map.c normalize_map.c do_transform.c)

include_directories(. ./libft ./ft_printf)
if (LINUX)
    include_directories(./minilibx)
    find_library(MLX mlx ./minilibx)
    find_library(XEXT Xext /usr/lib/x86_64-linux-gnu/)
    find_library(X11 X11 /usr/lib/x86_64-linux-gnu/)
    target_link_libraries(fdf PUBLIC ${XEXT} ${X11})
else()
    include_directories(./minilibx_macos)
    find_library(MLX mlx ./minilibx_macos)
    target_link_libraries(fdf PUBLIC "-framework AppKit" "-framework OpenGL")
endif()

find_library(FT ft ./libft)
find_library(FTPF ftprintf ./ft_printf)
target_link_libraries(fdf PUBLIC ${FT} ${MLX} ${FTPF})
