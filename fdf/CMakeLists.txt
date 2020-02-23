cmake_minimum_required(VERSION 3.14)
project(fdf C)

set(CMAKE_C_STANDARD 11)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

add_executable(fdf
        src/fdf.c
        src/read_map.c
        src/draw_main.c
        src/init_images.c
        src/mouse_moves.c
        src/getters.c
        src/transforms.c
        src/draw_line.c
        src/mouse_hook.c
        src/key_hook.c
        src/colorize_map.c
        src/normalize_map.c
        src/do_transform.c
        src/draw_woo.c
        src/other_hooks.c
        src/setters.c
        )

include_directories(.
        ./includes
        ./libft/includes
        ./ft_printf/includes)
if (LINUX)
    include_directories(./minilibx)
    find_library(MLX mlx ./minilibx)
    find_library(XEXT Xext /usr/lib/x86_64-linux-gnu/)
    find_library(X11 X11 /usr/lib/x86_64-linux-gnu/)
    target_link_libraries(fdf PUBLIC ${XEXT} ${X11})
else()
    include_directories(./minilibx_macos)
    find_library(MLX mlx ./minilibx_macos)
    target_link_libraries(fdf "-framework AppKit" "-framework OpenGL")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libft ft)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ft_printf ftprintf)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/minilibx_macos mlx)
target_link_libraries(fdf ft ftprintf mlx)