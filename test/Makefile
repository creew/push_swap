SRC = main.c long_ariph.c sub_func.c
OBJ = $(SRC:.c=.o)
CC = gcc
CC_FLAGS = -Wall -Wextra
NAME = test

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CC_FLAGS) $^ -o $@

%.o: %.c 
	$(CC) $(CC_FLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all