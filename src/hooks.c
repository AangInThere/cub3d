#include "header.h"

int key_win(int key, t_cub *cub)
{
	(void)cub;
	// printf("Key in Win1 : %d\n", key);
	if (key == 0xFF1B)
		exit(0);
	else if (key == 119)
		cub->player.dir_ver = 1;
	else if (key == 115)
		cub->player.dir_ver = -1;
	else if (key == 97)
		cub->player.dir_hor = -1;
	else if (key == 100)
		cub->player.dir_hor = 1;
	else if (key == 65361)
		cub->player.turn_dir = -1;
	else if (key == 65363)
		cub->player.turn_dir = 1;
	return 1;
}

int key_release_win(int key, t_cub *cub)
{
	(void)cub;
	// printf("Key Release in Win1 : %d\n", key);
	if (key == 119)
		cub->player.dir_ver = 0;
	else if (key == 115)
		cub->player.dir_ver = 0;
	else if (key == 97)
		cub->player.dir_hor = 0;
	else if (key == 100)
		cub->player.dir_hor = 0;
	else if (key == 65361)
		cub->player.turn_dir = 0;
	else if (key == 65363)
		cub->player.turn_dir = 0;
	return 1;
}

int destroy_win(t_cub *cub)
{
	(void)cub;
	exit(0);
}
