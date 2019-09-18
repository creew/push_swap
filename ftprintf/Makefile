# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 09:49:46 by eklompus          #+#    #+#              #
#    Updated: 2019/09/18 23:04:38 by eklompus         ###   ########.fr        #
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
		sub_functions.c \
		add_unsigned.c \
		parse_unsigned.c \
		parse_signed.c \
		parse_double.c \
		add_double.c \
		calc_double.c \
		long_ariph.c


OBJ = $(SRCS:.c=.o)

INC = ./libft

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror -g $(addprefix -I, $(INC))

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CC_FLAGS) -o $@ $^ -Llibft -lft
#	ar rc $@ $^ libft/*.o

%.o: %.c ./ft_printf.h
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	make clean -C ./libft
	/bin/rm -rf $(OBJ)

fclean: clean
	/bin/rm -rf ./libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all
