cmake_minimum_required(VERSION 3.14)
project(checker C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        ../ft_printf/includes
        ../libft/includes
        ../common_dir/includes)

add_executable(checker
        srcs/checker.c
        ../common_dir/srcs/stack_action.c
        ../common_dir/srcs/stack.c
        ../common_dir/srcs/stack_sec.c
        ../common_dir/srcs/readarg.c
        ../common_dir/srcs/sub_functions.c
        ../common_dir/srcs/print_stacks.c
        )

#add_dependencies(checker libft_target libftprintf_target)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ft_printf ftprintf)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libft ft)
target_link_libraries(checker ft ftprintf)
