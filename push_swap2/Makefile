# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 15:23:14 by eklompus          #+#    #+#              #
#    Updated: 2019/09/23 20:09:16 by eklompus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHECKER = checker

PUSHSWAP = push_swap

CHECKER_DIR = ./checker_src

PUSHSWAP_DIR = ./push_swap_src

COMMON_DIR = ./common

CC = gcc

CC_FLAGS = -Wall -Wextra -g

CC_FERROR = #-Werror

CHECKER_SRC = checker.c

PUSHSWAP_SRC = \
		push_swap.c \
		paste_values.c \
		find_solution.c \
		sort_stack.c \
		diffs.c

COMMON_SRC = \
		stack.c \
    	sub_functions.c \
   	 	stack_sec.c \
    	readarg.c \
    	stack_action.c

CHECKER_OBJ = $(addprefix $(CHECKER_DIR)/,$(CHECKER_SRC:.c=.o))

PUSHSWAP_OBJ = $(addprefix $(PUSHSWAP_DIR)/,$(PUSHSWAP_SRC:.c=.o))

COMMON_OBJ = $(addprefix $(COMMON_DIR)/,$(COMMON_SRC:.c=.o))

INC_DIR =	./libft \
			./common \

INC_FLAG = $(addprefix -I,$(INC_DIR))

CHECKER_HEADERS = $(CHECKER_DIR)/checker.h ./libft/libft.h

PUSHSWAP_HEADERS = $(PUSHSWAP_DIR)/push_swap.h ./libft/libft.h

COMMON_HEADERS = $(COMMON_DIR)/common.h ./libft/libft.h

all: $(CHECKER) $(PUSHSWAP)

print:
	@echo $(PUSHSWAP_OBJ)
	@echo $(INC_FLAG)
	@echo $(PUSHSWAP_SRC)

$(CHECKER): $(CHECKER_OBJ) $(COMMON_OBJ)
	$(MAKE) -C ./libft
	$(CC) $(CC_FLAGS) $(CC_FERROR) $^ -L./libft -lft -o $@

$(PUSHSWAP): $(PUSHSWAP_OBJ) $(COMMON_OBJ)
	$(MAKE) -C ./libft
	$(CC) $(CC_FLAGS) $(CC_FERROR) $^ -L./libft -lft -o $@

$(CHECKER_DIR)/%.o: $(CHECKER_DIR)/%.c $(CHECKER_HEADERS) $(COMMON_HEADERS)
	$(CC) $(CC_FLAGS) $(CC_FERROR) $(INC_FLAG) -c $< -o $@

$(PUSHSWAP_DIR)/%.o: $(PUSHSWAP_DIR)/%.c $(PUSHSWAP_HEADERS) $(COMMON_HEADERS)
	$(CC) $(CC_FLAGS) $(CC_FERROR) $(INC_FLAG) -c $< -o $@

$(COMMON_DIR)/%.o: $(COMMON_DIR)/%.c $(COMMON_HEADERS)
	$(CC) $(CC_FLAGS) $(CC_FERROR) $(INC_FLAG) -c $< -o $@

clean:
	make clean -C ./libft
	rm -f $(CHECKER_OBJ)
	rm -f $(PUSHSWAP_OBJ)
	rm -f $(COMMON_OBJ)

fclean: clean
	rm -f ./libft/libft.a
	rm -f $(CHECKER)
	rm -f $(PUSHSWAP)

re: fclean all

.PHONY: all clean fclean re
