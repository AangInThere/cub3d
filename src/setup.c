/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:00:38 by aclose            #+#    #+#             */
/*   Updated: 2020/11/11 13:49:17 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	setup_cub3d(t_cub *cub)
{
	if (setup_window_and_image(cub) != 0)
		return (cub->error_code);
	cub->tile_size = TILE_SIZE;
	cub->player.speed = cub->tile_size / 8.0;
	cub->distance_projection_plane = (cub->window.width / 2)
											/ tan(FOV_ANGLE / 2);
	setup_hooks(cub);
	set_player_starting_position(&cub->player, cub->map, cub);
	cub->number_of_rays = cub->window.width / WALL_STRIP_WIDTH;
	if ((cub->rays = malloc(sizeof(t_ray) * (cub->number_of_rays))) == NULL)
		return (cub->error_code = MALLOC_ERROR);
	if (setup_sprites(cub) != 0)
		return (cub->error_code);
	return (0);
}

int	setup_window_and_image(t_cub *cub)
{
	if ((cub->window.win_ptr = mlx_new_window(cub->mlx_ptr, cub->window.width
			, cub->window.height, "Cub3D")) == NULL)
		return (cub->error_code = MINILIBX_ERROR);
	if ((cub->image.img_ptr = mlx_new_image(cub->mlx_ptr, cub->window.width
			, cub->window.height)) == NULL)
		return (cub->error_code = MINILIBX_ERROR);
	if ((cub->image.addr = mlx_get_data_addr(cub->image.img_ptr
			, &(cub->image.bits_per_pixel), &(cub->image.line_length)
			, &(cub->image.endian))) == NULL)
		return (cub->error_code = MINILIBX_ERROR);
	return (0);
}

int	set_player_starting_position(t_player *player, t_map map, t_cub *cub)
{
	static double	initial_angle[4] = {M_PI + M_PI / 2, M_PI, M_PI / 2, 0};
	static char		*player_string = "NWSE";
	int				i;
	int				j;

	i = -1;
	while (++i < map.height)
	{
		j = -1;
		while (++j < map.row_lengths[i])
		{
			if (ft_strchr(player_string, map.rows[i][j]) != NULL)
			{
				player->x = j * cub->tile_size + cub->tile_size / 2.0;
				player->y = i * cub->tile_size + cub->tile_size / 2.0;
				player->rotation_angle =
					initial_angle[(long)(ft_strchr(player_string
						, map.rows[i][j]) - player_string)];
				break ;
			}
		}
	}
	return (0);
}

int	setup_sprites(t_cub *cub)
{
	int i;
	int j;
	int k;

	cub->map.sprite_count = ft_count_sprites(&cub->map);
	if ((cub->map.sprites = malloc(sizeof(t_sprite) * cub->map.sprite_count))
			== NULL)
		return (cub->error_code = MALLOC_ERROR);
	i = -1;
	k = 0;
	while (++i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.row_lengths[i])
		{
			if (cub->map.rows[i][j] == SPRITE)
			{
				cub->map.sprites[k].x = cub->tile_size * j + cub->tile_size / 2;
				cub->map.sprites[k++].y = cub->tile_size * i
						+ cub->tile_size / 2;
			}
			j++;
		}
	}
	return (0);
}

int	ft_count_sprites(t_map *map)
{
	int i;
	int j;

	i = -1;
	while (++i < map->height)
	{
		j = 0;
		while (j < map->row_lengths[i])
		{
			if (map->rows[i][j] == SPRITE)
				map->sprite_count++;
			j++;
		}
	}
	return (map->sprite_count);
}
