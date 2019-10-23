#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 10:49:41 by eklompus          #+#    #+#              #
#    Updated: 2019/10/23 10:49:41 by eklompus         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = push_swap

CC = gcc

CC_FLAGS = -Wall -Wextra #-Werror

SRCS = push_swap.c \
        ./../common/check_arr.c \
        ./../common/stack_action.c \
        ./../common/stack.c \
        ./../common/stack_sec.c \
        ./../common/readarg.c \
        ./../common/sub_functions.c \
        ./../common/actions.c \
        ./../common/dllist.c

OBJS = $(SRCS:.c=.o)

LIBFT = ft

LIBFT_PATH = ./../libft

HEADERS_PATH = \
	. \
	./../common \
	./../libft

I_FLAG = $(addprefix -I,$(HEADERS_PATH))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -L$(LIBFT_PATH) -l$(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CC_GLAGS) -c $(I_FLAG) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)