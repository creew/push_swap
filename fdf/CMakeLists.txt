cmake_minimum_required(VERSION 3.14)
project(fdf C)

set(CMAKE_C_STANDARD 11)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

add_executable(fdf
        fdf.c
        read_map.c
        draw_main.c
        init_images.c
        mouse_moves.c
        getters.c
        transforms.c
        draw_line.c
        mouse_hook.c
        key_hook.c
        colorize_map.c
        normalize_map.c
        do_transform.c
        draw_woo.c
        other_hooks.c
        setters.c
        )

include_directories(.
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