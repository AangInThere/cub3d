#include "header.h"

int update_player(t_cub *cub)
{
	double newx;
	double newy;
	double deltax;
	double deltay;
	t_player *player = &cub->player;
	deltax = player->dir_ver * YSPEED * cos(player->rotation_angle) + player->dir_hor * XSPEED * cos(player->rotation_angle + M_PI / 2);
	deltay = player->dir_ver * YSPEED * sin(player->rotation_angle) + player->dir_hor * XSPEED * sin(player->rotation_angle + M_PI / 2);
	newx = player->x + deltax;
	newy = player->y + deltay;
	// printf("new player.x: %f, new player.y: %f\n", newx, newy);
	// printf("delta.x: %f, delta.y: %f\n", deltax, deltay);

	if (!(WallAt(newx, newy, cub->map, cub)))
	{
		// printf("pos of player changed\n");
		player->x = newx;
		player->y = newy;
	}
	player->rotation_angle += player->turn_dir * ROTATION_SPEED;
	player->rotation_angle = normalize_angle(player->rotation_angle);
	// printf("rotation_angle: %f\n", player->rotation_angle);
	// player->dir_hor = 0;
	// player->dir_ver = 0;
	// player->turn_dir = 0;
	return 1;
}

int WallAt(int x, int y, t_map map, t_cub *cub)
{
	// int xInGrid = x / TILE_SIZE;
	// int yInGrid = y / TILE_SIZE;
	// if (grid[yInGrid][xInGrid] == 1 || x < 0 || y < 0)
	// 	return (1);
	// else
	// 	return (0);

	int xInGrid = x / cub->tile_size;
	int yInGrid = y / cub->tile_size;
	// if (x < 0 || y < 0 || y >= map.height || x >= (int)ft_strlen(map.rows[yInGrid]) || map.rows[yInGrid][xInGrid] == 1)
	// remove ft_strlen add something in map because otherwise it is going to be too slow
	if (x < 0 || y < 0 || yInGrid >= map.height || xInGrid >= (int)ft_strlen(map.rows[yInGrid]) || map.rows[yInGrid][xInGrid] == WALL)
		return (1);
	else
		return (0);
}
