NAME = cub3d
CC=gcc
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
CFLAGS=-g -Wall -Wextra -Werror -I $(INC_DIR)
#CFLAGS= -I$(INC) -O3 -I..

_SRC = myTest.c player.c helper_render.c ray.c
SRC = $(addprefix $(SRC_DIR)/,$(_SRC))
_HEADER=header.h
HEADER = $(addprefix $(INC_DIR)/,$(_HEADER))

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L. -lmlx -lXext -lX11 -lm -lbsd -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

info:
	$(info    VAR is $(SRC))

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
