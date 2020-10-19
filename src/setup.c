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
	cub->tile_width = cub->window.width / cub->map.width;
	cub->tile_height = cub->window.height / cub->map.height;

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
