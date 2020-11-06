#include "header.h"

int setup_cub3d(t_cub *cub)
{

	if (setup_window_and_images(cub) != 0)
		return (cub->error_code);
	cub->tile_size = ft_compute_tile_size(cub);
	// cub->tile_size = TILE_SIZE;
	cub->tile_width = cub->window.width / cub->map.width;
	cub->tile_height = cub->window.height / cub->map.height;
	setup_hooks(cub);
	set_player_starting_position(&cub->player, cub->map, cub);
	cub->number_of_rays = cub->window.width / WALL_STRIP_WIDTH;
	if ((cub->rays = malloc(sizeof(t_ray) * (cub->number_of_rays))) == NULL)
		return (cub->error_code = MALLOC_ERROR);
	if (setup_sprites(cub) != 0)
		return (cub->error_code);
	return (0);
}

int setup_window_and_images(t_cub *cub)
{
	if ((cub->window.win_ptr = mlx_new_window(cub->mlx_ptr, cub->window.width, cub->window.height, "Cub3D")) == NULL)
		return (cub->error_code = MINILIBX_ERROR);
	if ((cub->images[0].img_ptr = mlx_new_image(cub->mlx_ptr, cub->window.width, cub->window.height)) == NULL)
		return (cub->error_code = MINILIBX_ERROR);
	if ((cub->images[1].img_ptr = mlx_new_image(cub->mlx_ptr, cub->window.width, cub->window.height)) == NULL)
		return (cub->error_code = MINILIBX_ERROR);
	if ((cub->images[0].addr = mlx_get_data_addr(cub->images[0].img_ptr, &(cub->images[0].bits_per_pixel), &(cub->images[0].line_length),
												 &(cub->images[0].endian))) == NULL)
		return (cub->error_code = MINILIBX_ERROR);
	if ((cub->images[1].addr = mlx_get_data_addr(cub->images[1].img_ptr, &(cub->images[1].bits_per_pixel), &(cub->images[1].line_length),
												 &(cub->images[1].endian))) == NULL)
		return (cub->error_code = MINILIBX_ERROR);
	return (0);
}

int	setup_hooks(t_cub *cub)
{
	mlx_hook(cub->window.win_ptr, 2, 1L << 0, key_win, cub);
	mlx_hook(cub->window.win_ptr, 3, 1L << 1, key_release_win, cub);
	mlx_hook(cub->window.win_ptr, 17, 1L << 17, destroy_win, cub);
	mlx_loop_hook(cub->mlx_ptr, render_next_frame, cub);
	return (0);
}

int set_player_starting_position(t_player *player, t_map map, t_cub *cub)
{
	static double initial_angle[4] = {M_PI + M_PI / 2, 0, M_PI / 2, M_PI};
	static char *player_string = "NWSE";

	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < (int)ft_strlen(map.rows[i]); j++)
		{
			if (ft_strchr(player_string, map.rows[i][j]) != NULL)
			{
				player->x = j * cub->tile_size + cub->tile_size / 2.0;
				player->y = i * cub->tile_size + cub->tile_size / 2.0;
				player->rotation_angle = initial_angle[(long)(ft_strchr(player_string, map.rows[i][j]) - player_string)];
				break;
			}
		}
	}
	return (0);
}

int ft_compute_tile_size(t_cub *cub)
{
	int according_to_width;
	int according_to_height;

	according_to_width = cub->window.width / cub->map.width;
	according_to_height = cub->window.height / cub->map.height;
	return (according_to_width < according_to_height ? according_to_width : according_to_height);
}

int setup_sprites(t_cub *cub)
{
	int i;
	int j;
	int k;

	cub->map.sprite_count = ft_count_sprites(&cub->map);
	if ((cub->map.sprites = malloc(sizeof(t_sprite) * cub->map.sprite_count)) == NULL)
		return (cub->error_code = MALLOC_ERROR);
	i = -1;
	k = 0;
	while (++i < cub->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(cub->map.rows[i]))
		{
			if (cub->map.rows[i][j] == SPRITE)
			{
				cub->map.sprites[k].x = cub->tile_size * j + cub->tile_size / 2;
				cub->map.sprites[k++].y = cub->tile_size * i + cub->tile_size / 2;
			}
			j++;
		}
	}
	return (0);
}

int	ft_count_sprites(t_map *map)
{
	int i;
	int row_length;
	int j;

	i = -1;
	while (++i < map->height)
	{
		j = 0;
		row_length = ft_strlen(map->rows[i]);
		while (j < row_length)
		{
			if (map->rows[i][j] == SPRITE)
				map->sprite_count++;
			j++;
		}
	}
	return (map->sprite_count);
}
