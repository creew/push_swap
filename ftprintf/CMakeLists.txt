cmake_minimum_required(VERSION 3.14)
project(ftprintf C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ftprintf
        add_double.c
        add_paddings.c
        add_prefix.c
        add_to_out.c
        add_unsigned.c
        calc_double.c
        ft_printf.c
        ft_printf.h
        long_ariph.c
        parse_character.c
        parse_double.c
        parse_flags.c
        parse_format.c
        parse_lenmod.c
        parse_precision.c
        parse_signed.c
        parse_string.c
        parse_type.c
        parse_unsigned.c
        parse_width.c
        sub_functions.c
        test.c
        callbacks.c parse_colors.c)
