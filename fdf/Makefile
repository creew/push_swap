
NAME = fdf

CC = gcc

CC_FLAGS = -Wall -Wextra $(CC_FLAG_ERR)

CC_FLAG_ERR = #-Werror
SRCS = fdf.c

OBJS = $(SRCS:.c=.o)

LIBFT_LIB = ft
MINILIBX_LIB = mlx
FT_PRINTF_LIB = ftprintf

LIBFT_DIR = ./libft
MINILIBX_DIR = ./minilibx_macos
FT_PRINTF_DIR = ./ft_printf
INC_DIR = $(LIBFT_DIR) $(MINILIBX_DIR) $(FT_PRINTF_DIR)

IINC = $(addprefix -I,$(INC_DIR))
LINC = $(addprefix -L,$(INC_DIR))

LLIBS = $(addprefix -l,$(LIBFT_LIB) $(MINILIBX_LIB) $(FT_PRINTF_LIB))
FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MINILIBX_DIR)
	make -C $(FT_PRINTF_DIR)
	$(CC) $(CC_FLAGS) $(OBJS) $(LINC) $(LLIBS) $(FRAMEWORKS) -o $@

%.o: %.c
	$(CC) $(CC_FLAGS) $(IINC) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)
	make clean -C $(FT_PRINTF_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT_DIR)/lib$(LIBFT_LIB).a
	rm -f $(MINILIBX_DIR)/lib$(MINILIBX_LIB).a
	rm -f $(FT_PRINTF_DIR)/lib$(FT_PRINTF_LIB).a
	rm -f $(NAME)

re:	fclean all
