
NAME = fdf

CC = gcc

CC_FLAGS = -Wall -Wextra $(CC_FLAG_ERR)

CC_FLAG_ERR = #-Werror
SRCS =	fdf.c \
		read_map.c \
		init_images.c \
		draw_main.c \
		mouse_moves.c \
		transforms.c \
		getters.c \
		draw_line.c

OBJS = $(SRCS:.c=.o)

LIBFT_LIB = ft
MINILIBX_LIB = mlx
FT_PRINTF_LIB = ftprintf

LIBFT_DIR = ./libft
MMINILIBX_DIR = ./minilibx_macos
UMINILIBX_DIR = ./minilibx
FT_PRINTF_DIR = ./ft_printf
INC_DIR = $(LIBFT_DIR) $(MMINILIBX_DIR) $(FT_PRINTF_DIR)

IINC = $(addprefix -I,$(INC_DIR))
LINC = $(addprefix -L,$(INC_DIR))

UFRAMEWORKS = -lmlx -lXext -lX11 -lm
LLIBS = $(addprefix -l,$(LIBFT_LIB) $(MINILIBX_LIB) $(FT_PRINTF_LIB))
MFRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	#make -C $(MINILIBX_DIR)
	make -C $(FT_PRINTF_DIR)
	$(CC) $(CC_FLAGS) $(OBJS) $(LINC) $(LLIBS) $(MFRAMEWORKS) -o $@

%.o: %.c ./fdf.h
	$(CC) $(CC_FLAGS) $(IINC) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	#make clean -C $(MINILIBX_DIR)
	make clean -C $(FT_PRINTF_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT_DIR)/lib$(LIBFT_LIB).a
	#rm -f $(MINILIBX_DIR)/lib$(MINILIBX_LIB).a
	rm -f $(FT_PRINTF_DIR)/lib$(FT_PRINTF_LIB).a
	rm -f $(NAME)

re:	fclean all
