#include "header.h"

int set_up_window_and_images_for_cub(t_cub *cub)
{
	cub->window.win_ptr = mlx_new_window(cub->mlx_ptr, cub->window.width, cub->window.height, "Cub3D");
	cub->images[0].img_ptr = mlx_new_image(cub->mlx_ptr, cub->window.width, cub->window.height);
	cub->images[1].img_ptr = mlx_new_image(cub->mlx_ptr, cub->window.width, cub->window.height);
	cub->images[0].addr = mlx_get_data_addr(cub->images[0].img_ptr, &(cub->images[0].bits_per_pixel), &(cub->images[0].line_length),
											&(cub->images[0].endian));
	cub->images[1].addr = mlx_get_data_addr(cub->images[1].img_ptr, &(cub->images[1].bits_per_pixel), &(cub->images[1].line_length),
											&(cub->images[1].endian));
	mlx_hook(cub->window.win_ptr, 2, 1L << 0, key_win, cub);
	mlx_hook(cub->window.win_ptr, 3, 1L << 1, key_release_win, cub);
	mlx_hook(cub->window.win_ptr, 17, 1L << 17, destroy_win, cub);
	mlx_loop_hook(cub->mlx_ptr, render_next_frame, cub);
	cub->number_of_rays = cub->window.width / WALL_STRIP_WIDTH;
	cub->rays = malloc(sizeof(t_ray) * (cub->number_of_rays));
	cub->tile_size = ft_compute_tile_size(cub);
	// cub->tile_size = 80;
	cub->tile_width = cub->window.width / cub->map.width;
	cub->tile_height = cub->window.height / cub->map.height;
	cub->sprite.x = 1.5 * cub->tile_size;
	cub->sprite.y = 1.5 * cub->tile_size;
	return 0;
}

int set_player_starting_position(t_player *player, t_map map, t_cub *cub)
{
	static double initial_angle[4] = {M_PI + M_PI / 2, 0, M_PI / 2, M_PI};
	char *player_string = "NWSE";
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
	cub->map.sprites = malloc(sizeof(t_sprite) * cub->map.sprite_count);
	if (!cub->map.sprites)
		return (1);
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
