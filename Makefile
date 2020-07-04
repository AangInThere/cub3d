CC=gcc
CFLAGS=-g -Wall -Wextra -Werror

#CFLAGS= -I$(INC) -O3 -I..

SRC = myTest.c player.c helper_render.c ray.c
HEADER=header.h
OBJ = $(SRC:.c=.o)
all : $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -L. -lmlx -lXext -lX11 -lm -lbsd

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f a.out

re: fclean all
