cmake_minimum_required(VERSION 3.14)
project(pushswap C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        ../ft_printf/includes
        ../libft/includes
        ../common)

add_executable(pushswap
        push_swap.c
        find_solution.c
        paste_values.c
        sort_stack.c
        diffs.c
        ../common/stack_action.c
        ../common/stack.c
        ../common/stack_sec.c
        ../common/readarg.c
        ../common/sub_functions.c
        ../common/print_stacks.c find_max_seq.c find_median.c find_optimal.c)

#add_dependencies(pushswap libft_target libftprintf_target)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ft_printf ftprintf)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libft ft)
target_link_libraries(pushswap ft ftprintf)