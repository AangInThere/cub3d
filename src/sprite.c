/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:45:06 by aclose            #+#    #+#             */
/*   Updated: 2020/11/09 22:45:24 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		sort_sprites(t_map *map)
{
	int			i;
	t_bool		a_permutation_occured;
	t_sprite	tmp;

	a_permutation_occured = TRUE;
	while (a_permutation_occured)
	{
		a_permutation_occured = FALSE;
		i = 0;
		while (i < map->sprite_count - 1)
		{
			if (map->sprites[i].distance < map->sprites[i + 1].distance)
			{
				tmp = map->sprites[i];
				map->sprites[i] = map->sprites[i + 1];
				map->sprites[i + 1] = tmp;
				a_permutation_occured = TRUE;
			}
			i++;
		}
	}
	return (0);
}

int		update_sprites(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map.sprite_count)
	{
		update_sprite(&cub->map.sprites[i], cub->player, cub);
		i++;
	}
	sort_sprites(&cub->map);
	return (0);
}

void	update_sprite(t_sprite *sprite, t_player player, t_cub *cub)
{
	double difference_in_angle;

	sprite->dx = sprite->x - player.x;
	sprite->dy = sprite->y - player.y;
	sprite->distance = distance_between(sprite->x, sprite->y
													, player.x, player.y);
	sprite->angle = atan2(sprite->dy, sprite->dx);
	difference_in_angle = sprite->angle - player.rotation_angle;
	if (difference_in_angle < -1 * M_PI)
		difference_in_angle += 2 * M_PI;
	else if (difference_in_angle > M_PI)
		difference_in_angle -= 2 * M_PI;
	sprite->distance *= cos(difference_in_angle);
	difference_in_angle = fabs(difference_in_angle);
	sprite->is_visible = (difference_in_angle < FOV_ANGLE / 2 ? TRUE : FALSE);
	if (sprite->is_visible)
	{
		sprite->height = cub->tile_size * cub->distance_projection_plane
							/ sprite->distance;
		sprite->width = sprite->height;
		sprite->initial_x = tan(sprite->angle - player.rotation_angle)
			* cub->distance_projection_plane
			+ cub->window.width / 2 - sprite->width / 2;
		sprite->initial_y = cub->window.height / 2 - sprite->height / 2;
	}
}

int		render_sprites(t_image *img, t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map.sprite_count)
	{
		render_sprite(img, cub, &cub->map.sprites[i]);
		i++;
	}
	return (0);
}

void	render_sprite(t_image *img, t_cub *cub, t_sprite *sprite)
{
	unsigned	color;
	double		cur_x;
	double		cur_y;

	if (!sprite->is_visible)
		return ;
	cur_x = sprite->initial_x;
	while ((cur_x - sprite->initial_x) < sprite->width)
	{
		cur_y = sprite->initial_y;
		while (cur_y < cub->window.height / 2 + sprite->height / 2)
		{
			if (cur_x < cub->window.width && cur_y < cub->window.height
				&& cur_x >= 0 && cur_y >= 0
				&& cub->rays[(int)cur_x].distance > sprite->distance)
			{
				color = get_color_from_texture(&cub->textures[4]
							, sprite, cur_x, cur_y);
				if (color << 8)
					my_mlx_pixel_put(img, cur_x, cur_y, color);
			}
			cur_y++;
		}
		cur_x++;
	}
}
