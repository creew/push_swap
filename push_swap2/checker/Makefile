# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 10:56:58 by eklompus          #+#    #+#              #
#    Updated: 2019/09/24 16:15:15 by eklompus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

CC = gcc

CC_FLAGS = -Wall -Wextra -g

CC_FERROR = #-Werror

SRC =	checker.c \
		../common/stack.c \
		../common/sub_functions.c \
		../common/stack_sec.c \
		../common/readarg.c \
		../common/stack_action.c

OBJ = $(SRC:.c=.o)

INC_DIR =	./../ \
			./../libft

INC_FLAG = $(addprefix -I,$(INC_DIR))

HEADERS = ./checker.h ./../common/common.h ./../libft/libft.h

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../libft
	$(CC) $(CC_FLAGS) $(CC_FERROR) -L./../libft/ -lft $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(CC_FERROR) $(INC_FLAG) -c $< -o $@

clean:
	make clean -C ../libft
	rm -f $(OBJ)

fclean: clean
	rm -f ./../libft/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
