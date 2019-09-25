# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 10:56:58 by eklompus          #+#    #+#              #
#    Updated: 2019/09/24 16:28:19 by eklompus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = gcc

CC_FLAGS = -Wall -Wextra -g

CC_FERROR = #-Werror

SRC = push_swap.c \
	../common/stack.c \
	../common/sub_functions.c \
	../common/stack_sec.c \
	../common/readarg.c

OBJ = $(SRC:.c=.o)

INC_DIR = ./../

INC = ./push_swap.h $(INC_DIR)/common/common.h $(INC_DIR)libft/libft.h

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../libft
	$(CC) $(CC_FLAGS) $(CC_FERROR) -L./../libft/ -lft $^ -o $@

%.o: %.c $(INC)
	 $(CC) $(CC_FLAGS) $(CC_FERROR) -I$(INC_DIR) -c $< -o $@

clean:
	make clean -C ../libft
	rm -f $(OBJ)

fclean: clean
	rm -f ./../libft/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
