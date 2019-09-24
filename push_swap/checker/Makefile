# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 10:56:58 by eklompus          #+#    #+#              #
#    Updated: 2019/09/24 11:42:54 by eklompus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

CC = gcc

CC_FLAGS = -Wall -Wextra -g

CC_FERROR = #-Werror

SRC = checker.c ../common/stack.c ../common/sub_functions.c ../common/stack_sec.c

OBJ = $(SRC:.c=.o)

INC_DIR = ./../

INC = ./checker.h $(INC_DIR)/common/common.h $(INC_DIR)libft/libft.h

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../libft
	$(CC) $(CC_FLAGS) $(CC_FERROR) -L./../libft/ -lft $^ -o $@

%.o: %.c $(INC)
	 $(CC) $(CC_FLAGS) $(CC_FERROR) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
