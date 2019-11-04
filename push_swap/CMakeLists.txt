cmake_minimum_required(VERSION 3.14)
project(push_swap)

add_custom_target(
        libft_target
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/libft
)

add_custom_target(
        libftprintf_target
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/ft_printf
)

add_subdirectory(push_swap_src)
add_subdirectory(checker_src)
