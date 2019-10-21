cmake_minimum_required(VERSION 3.14)
project(pushswap C)

set(CMAKE_C_STANDARD 11)

include_directories(.
        ./../libft
        ./../common)

add_executable(pushswap
        push_swap.c
        ./../common/check_arr.c
        ./../common/stack_action.c
        ./../common/stack.c
        ./../common/stack_sec.c
        ./../common/readarg.c
        ./../common/sub_functions.c
        ./../common/actions.c
        )

find_library(FT ft ./../libft)
target_link_libraries(pushswap PUBLIC ${FT})