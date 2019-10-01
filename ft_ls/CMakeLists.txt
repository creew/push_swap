cmake_minimum_required(VERSION 3.14)
project(ft_ls)

set(CMAKE_C_STANDARD 99)

add_executable(ft_ls ft_ls.c ft_ls.h parse_args.c read_dir.c sub_funcs.c
        print_entry.c writeout.c print_sub.c time_sub.c)

include_directories(./libft)

find_library(FT ft ./libft)
target_link_libraries(ft_ls PUBLIC ${FT})
