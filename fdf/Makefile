
NAME = fdf

CC = gcc

CC_FLAGS = -Wall -Wextra $(CC_FLAG_ERR)

CC_FLAG_ERR = #-Werror
SRCS = fdf.c

OBJS = $(SRCS:.c=.o)

INC_DIR = ./libft ./minilibx_macos
IINC = $(addprefix -I,$(INC_DIR))
LINC = $(addprefix -L,$(INC_DIR))

FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) $(LINC) -lft -lmlx $(FRAMEWORKS) -o $@

%.o: %.c
	$(CC) $(CC_FLAGS) $(IINC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all
