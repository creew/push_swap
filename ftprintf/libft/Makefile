# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 09:49:46 by eklompus          #+#    #+#              #
#    Updated: 2019/09/13 18:38:01 by eklompus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
OBJ = $(SRCS:.c=.o)
SRCS = $(wildcard ft_*.c)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $@ $^
	ranlib $@

%.o: %.c libft.h
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
