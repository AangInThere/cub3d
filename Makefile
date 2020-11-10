NAME = cub3D
CC=gcc
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
CFLAGS=-ggdb3 -fsanitize=address -Wall -Wextra -Werror -I $(INC_DIR) -I minilibx-linux
# CFLAGS=-ggdb3 -Wall -Wextra -Werror -I $(INC_DIR) -I minilibx-linux
# CFLAGS=-O3 -Wall -Wextra -Werror -I $(INC_DIR) -I minilibx-linux

_SRC = cub3d.c player.c helper_render.c parse/parse_resolution.c parse/parse_utils.c \
		parse/parse_texture.c parse/parse_color.c parse/parse_premap.c parse/parse_map.c parse/check_map.c \
		parse/parse.c hooks.c render_minimap.c raycasting.c helper_raycasting.c \
		render_next_frame.c setup.c sprite.c save_bmp.c error.c setup_helper.c
SRC = $(addprefix $(SRC_DIR)/,$(_SRC))
_HEADER=header.h
HEADER = $(addprefix $(INC_DIR)/,$(_HEADER))

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C ./libft
	@make -C ./minilibx-linux
	$(CC) $(CFLAGS) $(OBJ) -Lminilibx-linux -lmlx -lXext -lX11 -lm -lbsd -Llibft -lft -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p obj/parse
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C ./libft clean
	@make -C ./minilibx-linux clean
	rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C ./libft fclean
	@make -C ./minilibx-linux fclean
	rm -f $(NAME)

re: fclean all

norminette:
	~/.norminette/norminette.rb $(SRC) $(HEADER)
