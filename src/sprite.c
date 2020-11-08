#include "header.h"

int	sort_sprites(t_map *map)
{
	int i;
	t_bool a_permutation_occured;
	t_sprite	tmp;
	a_permutation_occured = TRUE;

	while (a_permutation_occured)
	{
		a_permutation_occured = FALSE;
		i = 0;
		while (i < map->sprite_count - 1)
		{
			if (map->sprites[i].distance_from_player < map->sprites[i + 1].distance_from_player)
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

int update_sprites(t_cub *cub)
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

void update_sprite(t_sprite *sprite, t_player player, t_cub *cub)
{
	double difference_in_angle;

	sprite->dx = sprite->x - player.x;
	sprite->dy = sprite->y - player.y;
	sprite->distance_from_player = distanceBetween(sprite->x, sprite->y
													, player.x, player.y);
	sprite->angle = atan2(sprite->dy, sprite->dx);
	difference_in_angle = sprite->angle - player.rotation_angle;
	if (difference_in_angle < -1 * M_PI)
		difference_in_angle += 2 * M_PI;
	else if (difference_in_angle > M_PI)
		difference_in_angle -= 2 * M_PI;
	sprite->distance_from_player *= cos(difference_in_angle);
	difference_in_angle = fabs(difference_in_angle);
	sprite->is_visible = (difference_in_angle < FOV_ANGLE / 2 ? TRUE : FALSE);
	if (sprite->is_visible)
	{
		sprite->height = (sprite->distance_from_player / cub->tile_size)
			* cub->distance_projection_plane;
		sprite->width = sprite->height;

	}
}


int render_sprites(t_image *img, t_cub *cub)
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

int render_sprite(t_image *img, t_cub *cub, t_sprite *sprite)
{
	t_texture *texture = cub->textures + 4;
	if (sprite->is_visible)
	{
		double height = cub->tile_size * cub->distance_projection_plane / sprite->distance_from_player;
		double width = height;
		double x0 = tan(sprite->angle - cub->player.rotation_angle) * cub->distance_projection_plane + cub->window.width / 2;
		double inx = x0 - width / 2;
		double iny = cub->window.height / 2 - height / 2;
		double cx = 0;
		double texx, texy;
		while (cx < width)
		{
			double cy = 0;
			texx = cx * 64 / width;
			int ray_sprite = inx + cx;
			while (cy < height)
			{

				texy = cy * 64 / height;
				if (inx + cx < cub->window.width && iny + cy < cub->window.height && inx + cx >= 0 && iny + cy >= 0
					&& cub->rays[ray_sprite].distance > sprite->distance_from_player)
				{
					unsigned color;
					color = *(unsigned int *)(texture->img.addr + (int)texy * texture->img.line_length + (int)texx * (texture->img.bits_per_pixel / 8));
					if (color << 8)
						my_mlx_pixel_put(img, inx + cx, iny + cy, color);
					// my_mlx_pixel_put(img, inx + cx, iny + cy, 0XFFFFFF);
				}
				cy++;
			}
			cx++;
		}
	}
	return (0);
}
