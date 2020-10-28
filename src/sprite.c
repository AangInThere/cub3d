#include "header.h"

int update_sprite(t_cub *cub)
{
	double difference_in_angle;
	double sprite_angle_with_player;

	double dx = cub->sprite.x - cub->player.x;
	double dy = cub->sprite.y - cub->player.y;
	cub->sprite.distance_from_player = distanceBetween(cub->sprite.x, cub->sprite.y, cub->player.x, cub->player.y);
	sprite_angle_with_player = atan2(dy, dx);
	difference_in_angle = sprite_angle_with_player - cub->player.rotation_angle;
	if (difference_in_angle < -1 * M_PI)
		difference_in_angle += 2 * M_PI;
	else if (difference_in_angle > M_PI)
		difference_in_angle -= 2 * M_PI;
	cub->sprite.angle = difference_in_angle;
	difference_in_angle = (difference_in_angle > 0 ? difference_in_angle : -1 * difference_in_angle);
	if (difference_in_angle < FOV_ANGLE / 2)
		cub->sprite.is_visible = TRUE;
	else
		cub->sprite.is_visible = FALSE;
	printf("is_sprite visible: %s, filepath: %s\n", (cub->sprite.is_visible ? "YES" : "NO"), cub->textures[4].filepath);
	cub->sprite.distance_from_player *= cos(cub->sprite.angle);
	return (0);
}

int render_sprite(t_image *img, t_cub *cub)
{
	t_texture *texture = cub->textures + 4;
	if (cub->sprite.is_visible)
	{
		double dx = cub->sprite.x - cub->player.x;
		double dy = cub->sprite.y - cub->player.y;
		double distanceProjectionPlane = (cub->window.width / 2) / tan(FOV_ANGLE / 2);
		double height = cub->tile_size * distanceProjectionPlane / cub->sprite.distance_from_player;
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

		// double size = cub->window.width / cub->sprite.distance_from_player * cub->tile_size;
		// double x_offset = cub->sprite.angle * cub->window.width / FOV_ANGLE + cub->window.width /2 - size / 2;
		// double y_offset = cub->window.height /2 - size / 2;
		// // double SpriteHeight = (cub->tile_size / cub->sprite.distance_from_player) * distanceProjectionPlane;
		// // SpriteHeight = normalize_wall_height(SpriteHeight, cub);
		// // double y0 = cub->window.height / 2 - SpriteHeight / 2;
		// // double y1 = y0 + SpriteHeight;
		// // // double x_offset = cub->sprite.angle * cub->window.width / FOV_ANGLE + cub->window.width / 2 - SpriteHeight / 2;
		// // double x0 = tan(cub->sprite.angle) * cub->tile_size;
		// // double x = (cub->window.width / 2 + x0 - );
	}
	return (0);
}

// int render_sprite(t_cub *cub)
// {
// 	if (cub->sprite.is_visible)
// 	{
// 		double size = cub->window.width / cub->sprite.distance_from_player * cub->tile_size;
// 		double x_offset = cub->sprite.angle * cub->window.width / FOV_ANGLE + cub->window.width /2 - size / 2;
// 		double y_offset = cub->window.height /2 - size / 2;
// 		// double distanceProjectionPlane = (cub->window.width / 2) / tan(FOV_ANGLE / 2);
// 		// double SpriteHeight = (cub->tile_size / cub->sprite.distance_from_player) * distanceProjectionPlane;
// 		// SpriteHeight = normalize_wall_height(SpriteHeight, cub);
// 		// double y0 = cub->window.height / 2 - SpriteHeight / 2;
// 		// double y1 = y0 + SpriteHeight;
// 		// // double x_offset = cub->sprite.angle * cub->window.width / FOV_ANGLE + cub->window.width / 2 - SpriteHeight / 2;
// 		// double x0 = tan(cub->sprite.angle) * cub->tile_size;
// 		// double x = (cub->window.width / 2 + x0 - );
// 		int i;
// 		int j;
// 		unsigned color;
// 		t_texture *texture = cub->textures + 4;
// 		i = -1;
// 		j = -1;
// 		while (++i < size)
// 		{
// 			if (x_offset + i < 0 || x_offset + i > cub->window.width)
// 				continue;
// 			// if (cub->rays[(int)(x_offset + i)].distance <= cub->sprite.dist)
// 			// 	continue;
// 			j = -1;
// 			while (++j < size)
// 			{
// 				if (y_offset + j < 0 || y_offset + j > cub->window.height)
// 					continue;
// 				// color = cub->textures[4].img.addr[(int)(64 * (j * 64 / size) +
// 				// 								(i * 64 / size))];
// 				color = texture->img.addr[((int)(64 * (j * 64 / size) + (i * 64 / size)))];
// 				if (color)
// 					my_mlx_pixel_put(cub->images + cub->current_image ,(x_offset + i), (y_offset + j), color);
// 			}
// 		}
// 	}
// 	return (0);
// }
