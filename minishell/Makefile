#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 11:47:18 by eklompus          #+#    #+#              #
#    Updated: 2019/10/12 11:54:10 by eklompus         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = minishell

CC = gcc

CC_FLAGS = -Wall -Wextra

SRCS = minishell.c

OBJS = $(SRCS:.c=.o)

LIBFT_LIB = ft
LIBFT_DIR = ./libft


INC_DIR = $(LIBFT_DIR)

IINC = $(addprefix -I,$(INC_DIR))
LINC = $(addprefix -L,$(INC_DIR))
LLIBS = $(addprefix -l,$(LIBFT_LIB))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CC_FLAGS) $(OBJS) $(LINC) $(LLIBS) -o $@

%.o: %.c
	$(CC) $(CC_FLAGS) $(IINC) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT_DIR)/lib$(LIBFT_LIB).a
	rm -f $(NAME)

re:	fclean all
