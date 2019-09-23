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

all: $(CHECKER) $(PUSHSWAP)

$(CHECKER):
	make $(CHECKER) -C ./$(CHECKER)/

$(PUSHSWAP):
	make $(PUSHSWAP) -C ./$(PUSHSWAP)/

clean:
	make clean -C ./$(PUSHSWAP)/
	make clean -C ./$(CHECKER)/

fclean:
	make fclean -C ./$(PUSHSWAP)/
	make fclean -C ./$(CHECKER)/

re:
	make re -C ./$(CHECKER)/
	make re -C ./$(PUSHSWAP)/
