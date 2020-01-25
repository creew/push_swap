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

CC_FLAGS = -Wall -Wextra $(CC_FERROR) -g

CC_FERROR = #-Werror

SRC = push_swap.c \
	paste_values.c \
	find_solution.c \
	sort_stack.c \
	diffs.c \
	find_max_seq.c \
	find_median.c \
	../common/stack.c \
	../common/sub_functions.c \
	../common/stack_sec.c \
	../common/readarg.c \
	../common/stack_action.c

OBJ = $(SRC:.c=.o)

INC_DIR =	./../ \
			./../libft

INC_FLAG = $(addprefix -I,$(INC_DIR))

HEADERS = ./push_swap.h ./../common/common.h ./../libft/libft.h

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../libft
	$(CC) $(CC_FLAGS) -L./../libft/ -lft $^ -o $@

%.o: %.c $(INC)
	 $(CC) $(CC_FLAGS) $(INC_FLAG) -c $< -o $@

clean:
	make clean -C ../libft
	rm -f $(OBJ)

fclean: clean
	rm -f ./../libft/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
