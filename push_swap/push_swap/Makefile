# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 10:56:58 by eklompus          #+#    #+#              #
#    Updated: 2019/09/23 12:22:47 by eklompus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = gcc

CC_FLAGS = -Wall -Wextra

CC_FERROR = #-Werror

SRC = push_swap.c

OBJ = $(SRC:.c=.o)

INC_DIR = ./../

INC = ./push_swap.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CC_FLAGS) $(CC_FERROR) $^ -o $@

%.o: %.c $(INC) $(INC_DIR)common.h
	 $(CC) $(CC_FLAGS) $(CC_FERROR) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
