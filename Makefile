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

CHECKER_DIR = ./checker_dir

PUSHSWAP_DIR = ./push_swap_dir

all: $(CHECKER) $(PUSHSWAP)

$(CHECKER):
	$(MAKE) -C $(CHECKER_DIR)
	cp $(CHECKER_DIR)/$(CHECKER) .

$(PUSHSWAP):
	$(MAKE) -C $(PUSHSWAP_DIR)
	cp $(PUSHSWAP_DIR)/$(PUSHSWAP) .

clean:
	$(MAKE) clean -C $(CHECKER_DIR)
	$(MAKE) clean -C $(PUSHSWAP_DIR)

fclean: clean
	$(MAKE) fclean -C $(CHECKER_DIR)
	$(MAKE) fclean -C $(PUSHSWAP_DIR)
	rm -f $(CHECKER)
	rm -f $(PUSHSWAP)

re: fclean all

test:
	zsh supertest.sh -full 0 499 10

.PHONY: all clean fclean re test $(CHECKER) $(PUSHSWAP)
