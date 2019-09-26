# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/26 10:55:03 by eklompus          #+#    #+#              #
#    Updated: 2019/09/26 11:00:43 by eklompus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

CC_FLAGS = -Wall -Wextra $(CF_ERROR)

CF_ERROR = #-Werror

SRCS = ft_ls.c parse_args.c

HEADERS = ft_ls.h

OBJ = $(SRCS:.c=.o)

LIBFT_PATH = ./libft

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CC_FLAGS) -L$(LIBFT_PATH) -lft $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CC_FLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
