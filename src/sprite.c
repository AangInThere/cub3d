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
		update_sprite(&cub->map.sprites[i], cub->player);
		i++;
	}
	sort_sprites(&cub->map);
	return (0);
}

int update_sprite(t_sprite *sprite, t_player player)
{
	double difference_in_angle;
	double sprite_angle_with_player;

	double dx = sprite->x - player.x;
	double dy = sprite->y - player.y;
	sprite->distance_from_player = distanceBetween(sprite->x, sprite->y, player.x, player.y);
	sprite_angle_with_player = atan2(dy, dx);
	difference_in_angle = sprite_angle_with_player - player.rotation_angle;
	if (difference_in_angle < -1 * M_PI)
		difference_in_angle += 2 * M_PI;
	else if (difference_in_angle > M_PI)
		difference_in_angle -= 2 * M_PI;
	sprite->angle = difference_in_angle;
	difference_in_angle = (difference_in_angle > 0 ? difference_in_angle : -1 * difference_in_angle);
	if (difference_in_angle < FOV_ANGLE / 2)
		sprite->is_visible = TRUE;
	else
		sprite->is_visible = FALSE;
	// printf("is_sprite visible: %s, filepath: %s\n", (sprite->is_visible ? "YES" : "NO"), cub->textures[4].filepath);
	// sprite->distance_from_player *= cos(sprite->angle);
	return (0);
}

// int update_sprite(t_cub *cub)
// {
// 	double difference_in_angle;
// 	double sprite_angle_with_player;

// 	double dx = cub->sprite.x - cub->player.x;
// 	double dy = cub->sprite.y - cub->player.y;
// 	cub->sprite.distance_from_player = distanceBetween(cub->sprite.x, cub->sprite.y, cub->player.x, cub->player.y);
// 	sprite_angle_with_player = atan2(dy, dx);
// 	difference_in_angle = sprite_angle_with_player - cub->player.rotation_angle;
// 	if (difference_in_angle < -1 * M_PI)
// 		difference_in_angle += 2 * M_PI;
// 	else if (difference_in_angle > M_PI)
// 		difference_in_angle -= 2 * M_PI;
// 	cub->sprite.angle = difference_in_angle;
// 	difference_in_angle = (difference_in_angle > 0 ? difference_in_angle : -1 * difference_in_angle);
// 	if (difference_in_angle < FOV_ANGLE / 2)
// 		cub->sprite.is_visible = TRUE;
// 	else
// 		cub->sprite.is_visible = FALSE;
// 	// printf("is_sprite visible: %s, filepath: %s\n", (cub->sprite.is_visible ? "YES" : "NO"), cub->textures[4].filepath);
// 	return (0);
// }

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
	sprite->distance_from_player *= cos(sprite->angle);
	t_texture *texture = cub->textures + 4;
	if (sprite->is_visible)
	{
		double dx = sprite->x - cub->player.x;
		double dy = sprite->y - cub->player.y;
		double distanceProjectionPlane = (cub->window.width / 2) / tan(FOV_ANGLE / 2);
		double height = cub->tile_size * distanceProjectionPlane / sprite->distance_from_player;
		double width = height;
		double x0 = tan(atan2(dy,dx) - cub->player.rotation_angle) * distanceProjectionPlane + cub->window.width / 2;
		double inx = x0 - width / 2;
		double iny = cub->window.height / 2 - height / 2;
		double cx = 0;
		double texx, texy;
		while (cx < width)
		{
			double cy = 0;
			texx = cx * 64 / width;
			// int ray_sprite = inx + cx;
			while (cy < height)
			{

				texy = cy * 64 / height;
				if (inx + cx < cub->window.width && iny + cy < cub->window.height && inx + cx >= 0 && iny + cy >= 0)
				{
					unsigned color;
					color = *(unsigned int *)(texture->img.addr + (int)texy * texture->img.line_length + (int)texx * (texture->img.bits_per_pixel / 8));
					(void)color;
					if (color)
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

// int render_sprite(t_image *img, t_cub *cub)
// {
// 	cub->sprite.distance_from_player *= cos(cub->sprite.angle);
// 	t_texture *texture = cub->textures + 4;
// 	if (cub->sprite.is_visible)
// 	{
// 		double dx = cub->sprite.x - cub->player.x;
// 		double dy = cub->sprite.y - cub->player.y;
// 		double distanceProjectionPlane = (cub->window.width / 2) / tan(FOV_ANGLE / 2);
// 		double height = cub->tile_size * distanceProjectionPlane / cub->sprite.distance_from_player;
// 		double width = height;
// 		double x0 = tan(atan2(dy,dx) - cub->player.rotation_angle) * distanceProjectionPlane + cub->window.width / 2;
// 		double inx = x0 - width / 2;
// 		double iny = cub->window.height / 2 - height / 2;
// 		double cx = 0;
// 		double texx, texy;
// 		while (cx < width)
// 		{
// 			double cy = 0;
// 			texx = cx * 64 / width;
// 			// int ray_sprite = inx + cx;
// 			while (cy < height)
// 			{

// 				texy = cy * 64 / height;
// 				if (inx + cx < cub->window.width && iny + cy < cub->window.height && inx + cx >= 0 && iny + cy >= 0)
// 				{
// 					unsigned color;
// 					color = *(unsigned int *)(texture->img.addr + (int)texy * texture->img.line_length + (int)texx * (texture->img.bits_per_pixel / 8));
// 					(void)color;
// 					if (color)
// 						my_mlx_pixel_put(img, inx + cx, iny + cy, color);
// 					// my_mlx_pixel_put(img, inx + cx, iny + cy, 0XFFFFFF);
// 				}
// 				cy++;
// 			}
// 			cx++;
// 		}
// 	}
// 	return (0);
// }
