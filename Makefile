NAME = cub3d
CC=gcc
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
CFLAGS=-g -Wall -Wextra -Werror -I $(INC_DIR)
#CFLAGS= -I$(INC) -O3 -I..

_SRC = cub3d.c player.c helper_render.c ray.c parse_resolution.c parse_utils.c \
		parse_texture.c parse_color.c parse_premap.c parse_map.c check_map.c \

SRC = $(addprefix $(SRC_DIR)/,$(_SRC))
_HEADER=header.h
HEADER = $(addprefix $(INC_DIR)/,$(_HEADER))

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L. -lmlx -lXext -lX11 -lm -lbsd -Llibft -lft -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

_SANDBOX_SRC = check_map.c parse_map.c parse_premap.c parse_resolution.c parse_utils.c parse_texture.c parse_color.c
SANDBOX_SRC = $(addprefix $(SRC_DIR)/,$(_SANDBOX_SRC))

sandbox : sandbox.c $(SANDBOX_SRC) test.cub
	$(CC) -Wall -Wextra -g -I include sandbox.c $(SANDBOX_SRC) -L. -lmlx -lXext -lX11 -lm -lbsd -Llibft -lft -o sandbox && ./sandbox

info:
	$(info    VAR is $(SRC))

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
