#include "header.h"

// t_player player = {TILE_SIZE * 2, TILE_SIZE * 2, 0, 0, 0, 0.25 * M_PI};


void plot_circle(t_image *img, int xm, int ym, int r, unsigned color)
{
	int x = -r, y = 0, err = 2 - 2 * r; /* II. Quadrant */
	do
	{
		my_mlx_pixel_put(img, xm - x, ym + y, color); /*   I. Quadrant */
		my_mlx_pixel_put(img, xm - y, ym - x, color); /*  II. Quadrant */
		my_mlx_pixel_put(img, xm + x, ym - y, color); /* III. Quadrant */
		my_mlx_pixel_put(img, xm + y, ym + x, color); /*  IV. Quadrant */
		r = err;
		if (r > x)
			err += ++x * 2 + 1; /* e_xy+e_x > 0 */
		if (r <= y)
			err += ++y * 2 + 1; /* e_xy+e_y < 0 */
	} while (x < 0);
}

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

	if (!(WallAt(newx, newy, cub->map)))
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

int render_player(t_image* img, t_cub *cub)
{
	// put_square_at(img, player.x - PLAYER_SIZE / 2, player.y - PLAYER_SIZE / 2, PLAYER_SIZE, 0X00FF0000);
	plot_circle(img, MINIMAP_SCALE_FACTOR * cub->player.x , MINIMAP_SCALE_FACTOR * cub->player.y, PLAYER_SIZE, 0X00FF0000);
	return 1;
}

int WallAt(int x, int y, t_map map)
{
	// int xInGrid = x / TILE_SIZE;
	// int yInGrid = y / TILE_SIZE;
	// if (grid[yInGrid][xInGrid] == 1 || x < 0 || y < 0)
	// 	return (1);
	// else
	// 	return (0);

	int xInGrid = x / TILE_SIZE;
	int yInGrid = y / TILE_SIZE;
	// if (x < 0 || y < 0 || y >= map.height || x >= (int)ft_strlen(map.rows[yInGrid]) || map.rows[yInGrid][xInGrid] == 1)
	if (x < 0 || y < 0 || map.rows[yInGrid][xInGrid] == WALL)
		return (1);
	else
		return (0);
}
