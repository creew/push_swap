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

CHECKER_SRC = ./checker_src

PUSHSWAP = push_swap

PUSHSWAP_SRC = ./push_swap_src

all: $(CHECKER) $(PUSHSWAP) copy

copy:
	cp -f ./$(CHECKER_SRC)/$(CHECKER) .
	cp -f ./$(PUSHSWAP_SRC)/$(PUSHSWAP) .

$(CHECKER):
	make $(CHECKER) -C ./$(CHECKER_SRC)/

$(PUSHSWAP):
	make $(PUSHSWAP) -C ./$(PUSHSWAP_SRC)/

clean:
	make clean -C ./$(PUSHSWAP_SRC)/
	make clean -C ./$(CHECKER_SRC)/

fclean:
	make fclean -C ./$(PUSHSWAP_SRC)/
	make fclean -C ./$(CHECKER_SRC)/

re:
	make re -C ./$(CHECKER_SRC)/
	make re -C ./$(PUSHSWAP_SRC)/
