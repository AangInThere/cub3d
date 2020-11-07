#include "header.h"

int update_player(t_cub *cub)
{
	double	newx;
	double	newy;
	double	deltax;
	double	deltay;

	deltax = cub->player.dir_ver * YSPEED * cos(cub->player.rotation_angle)
			+ cub->player.dir_hor * XSPEED * cos(cub->player.rotation_angle + M_PI / 2);
	deltay = cub->player.dir_ver * YSPEED * sin(cub->player.rotation_angle)
			+ cub->player.dir_hor * XSPEED * sin(cub->player.rotation_angle + M_PI / 2);
	newx = cub->player.x + deltax;
	newy = cub->player.y + deltay;

	if (!(is_wall_at(newx, newy, cub->map, cub)) && !is_sprite_at(newx, newy, cub->map, cub))
	{
		cub->player.x = newx;
		cub->player.y = newy;
	}
	cub->player.rotation_angle += cub->player.turn_dir * ROTATION_SPEED;
	cub->player.rotation_angle = normalize_angle(cub->player.rotation_angle);
	return (0);
}

int is_wall_at(int x, int y, t_map map, t_cub *cub)
{
	int	x_in_grid;
	int	y_in_grid;

	x_in_grid = x / cub->tile_size;
	y_in_grid = y / cub->tile_size;
	// remove ft_strlen add something in map because otherwise it is going to be too slow
	if (x < 0 || y < 0 || y_in_grid >= map.height || x_in_grid >= (int)ft_strlen(map.rows[y_in_grid]) || map.rows[y_in_grid][x_in_grid] == WALL)
		return (1);
	else
		return (0);
}

int	is_sprite_at(int x, int y, t_map map, t_cub *cub)
{
	int	x_in_grid;
	int	y_in_grid;

	x_in_grid = x / cub->tile_size;
	y_in_grid = y / cub->tile_size;
	// remove ft_strlen add something in map because otherwise it is going to be too slow
	if (x < 0 || y < 0 || y_in_grid >= map.height || x_in_grid >= (int)ft_strlen(map.rows[y_in_grid]) || map.rows[y_in_grid][x_in_grid] == SPRITE)
		return (1);
	else
		return (0);
}
