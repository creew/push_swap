cmake_minimum_required(VERSION 3.14)
project(checker C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        ../ft_printf/includes
        ../libft/includes
        ../common)

add_executable(checker
        checker.c
        ../common/stack_action.c
        ../common/stack.c
        ../common/stack_sec.c
        ../common/readarg.c
        ../common/sub_functions.c
        ../common/print_stacks.c
        )

#add_dependencies(checker libft_target libftprintf_target)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ft_printf ftprintf)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libft ft)
target_link_libraries(checker ft ftprintf)
