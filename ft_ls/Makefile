# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eklompus <eklompus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/26 10:55:03 by eklompus          #+#    #+#              #
#    Updated: 2019/10/07 12:53:21 by eklompus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

CC_FLAGS = -Wall -Wextra -g $(CF_ERROR)

CF_ERROR = #-Werror

SRCS = ft_ls.c parse_args.c read_dir.c sub_funcs.c print_entry.c writeout.c \
		print_sub.c print_rights.c print_list.c time_sub.c callbacks.c \
		write_errors.c write_strings.c get_field_lengths.c get_vals.c \
		print_short.c

HEADERS = ft_ls.h

OBJ = $(SRCS:.c=.o)

LIBFT_PATH = ./libft/

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CC_FLAGS) $^ -L$(LIBFT_PATH) -lft -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CC_FLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all