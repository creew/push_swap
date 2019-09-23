# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 09:49:46 by eklompus          #+#    #+#              #
#    Updated: 2019/09/22 18:38:09 by eklompus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = 	ft_printf.c \
		parse_flags.c \
		parse_width.c \
		parse_precision.c \
		parse_lenmod.c \
		parse_type.c \
		parse_format.c \
		parse_character.c \
		parse_string.c \
		add_to_out.c \
		add_paddings.c \
		add_prefix.c \
		add_unsigned.c \
		parse_unsigned.c \
		parse_signed.c \
		parse_double.c \
		add_double.c \
		calc_double.c \
		sub_functions.c \
		long_ariph.c

SRC_TEST = test.c

OBJ = $(SRCS:.c=.o)

CC = gcc

CC_FLAGS = -Wall -Wextra -g

all: $(NAME)

test: $(NAME) $(SRC_TEST:.c=.o)
	$(CC) $(CC_FLAGS) -o $@ $^

$(NAME): $(OBJ)
	ar rc $@ $^

%.o: %.c ./ft_printf.h
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	/bin/rm -rf $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
