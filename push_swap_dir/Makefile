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

SRCDIR = ./srcs
OBJDIR = ./objs
INCLUDES = ./includes

COMMON_DIR = ./../common_dir
COMMON_OBJ_DIR = $(COMMON_DIR)/$(OBJDIR)
COMMON_SRC_DIR = $(COMMON_DIR)/$(SRCDIR)
COMMON_INCLUDES = $(COMMON_DIR)/$(INCLUDES)

CC_FERROR = #-Werror

COMMON_SRC = stack.c \
             sub_functions.c \
             stack_sec.c \
             readarg.c \
             stack_action.c \
             print_stacks.c

SRC =		push_swap.c \
			paste_values.c \
			find_optimal.c \
			find_solution.c \
			sort_stack.c \
			diffs.c \
			find_max_seq.c \
			find_median.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
COMMON_OBJ = $(COMMON_SRC:%.c=$(COMMON_DIR)/$(OBJDIR)/%.o)

COMMON_INC_DIR = $(COMMON_INCLUDES) \
			./../libft/includes \
            ./../ft_printf/includes

INC_DIR =	$(INCLUDES) \
			./../libft/includes \
			./../ft_printf/includes \
			$(COMMON_INCLUDES)

INC_FLAG = $(addprefix -I,$(INC_DIR))
COMMON_INC_FLAG = $(addprefix -I,$(COMMON_INC_DIR))

COMMON_HEADERS = $(COMMON_INCLUDES)/common.h \
			./../libft/includes/libft.h \
            ./../ft_printf/includes/ft_printf.h

HEADERS =	$(INCLUDES)/push_swap.h \
			./../libft/includes/libft.h \
			./../ft_printf/includes/ft_printf.h \
			$(COMMON_INCLUDES)/common.h

LIBFT_DIR = ./../libft
LIBFT_NAME = libft.a
LIBFT_LIB = ft

LIBFTPRINTF_DIR = ./../ft_printf
LIBFTPRINTF_NAME = libftprintf.a
LIBFTPRINTF_LIB = ftprintf

all: $(NAME)

$(NAME): $(LIBFT_DIR)/$(LIBFT_NAME) $(LIBFTPRINTF_DIR)/$(LIBFTPRINTF_NAME) $(OBJ) $(COMMON_OBJ)
	$(CC) $(CC_FLAGS) -L$(LIBFT_DIR) -L$(LIBFTPRINTF_DIR) $(COMMON_OBJ) $(OBJ)  -l$(LIBFT_LIB) -l$(LIBFTPRINTF_LIB) -o $@

$(LIBFT_DIR)/$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_NAME)

$(LIBFTPRINTF_DIR)/$(LIBFTPRINTF_NAME):
	$(MAKE) -C $(LIBFTPRINTF_DIR) $(LIBFTPRINTF_NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(INC_FLAG) -c $< -o $@

$(COMMON_OBJ_DIR)/%.o: $(COMMON_SRC_DIR)/%.c $(COMMON_HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(COMMON_INC_FLAG) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(LIBFTPRINTF_DIR)
	rm -f $(OBJ)
	rm -f $(COMMON_OBJ)

fclean: clean
	rm -f $(LIBFT_DIR)/$(LIBFT_NAME)
	rm -f $(LIBFTPRINTF_DIR)/$(LIBFTPRINTF_NAME)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
