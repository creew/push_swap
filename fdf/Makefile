
NAME = fdf

CC = gcc

CC_FLAGS = -Wall -Wextra $(CC_FLAG_ERR)

CC_FLAG_ERR = #-Werror
SRCS = fdf.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all
