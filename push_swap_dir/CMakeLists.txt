cmake_minimum_required(VERSION 3.14)
project(pushswap C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        includes
        ../ft_printf/includes
        ../libft/includes
        ../common_dir/includes)

add_executable(pushswap
        srcs/push_swap.c
        srcs/find_solution.c
        srcs/paste_values.c
        srcs/sort_stack.c
        srcs/diffs.c
        ../common_dir/srcs/stack_action.c
        ../common_dir/srcs/stack.c
        ../common_dir/srcs/stack_sec.c
        ../common_dir/srcs/readarg.c
        ../common_dir/srcs/sub_functions.c
        ../common_dir/srcs/print_stacks.c srcs/find_max_seq.c srcs/find_median.c srcs/find_optimal.c)

#add_dependencies(pushswap libft_target libftprintf_target)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ft_printf ftprintf)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libft ft)
target_link_libraries(pushswap ft ftprintf)