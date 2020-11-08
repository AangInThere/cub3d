#include "header.h"

int			render_next_frame(t_cub *cub)
{
	t_image *img = &cub->image;
	update_player(cub);
	update_rays(cub);
	// clear_img(img, cub);
	update_sprites(cub);
	render_walls_floor_and_ceiling(img, cub);
	render_sprites(img, cub);
	// render_player(img, cub);
	// render_grid(img, cub);
	// render_rays(img, cub);
	if (cub->should_save_first_frame)
		save_bmp_and_exit(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->window.win_ptr, img->img_ptr, 0, 0);
	return (0);
}

void		render_walls_floor_and_ceiling(t_image *img, t_cub *cub)
{
	t_ray	*ray;
	int		i;

	i = -1;
	while (++i < cub->number_of_rays)
	{
		ray = &cub->rays[i];
		ray->wall_strip_height = (cub->tile_size / ray->distance)
									* cub->distance_projection_plane;
		ray->normalized_wall_strip_height =
			normalize_wall_height(ray->wall_strip_height, cub);
		render_wall_strip(img, cub->rays[i], i, cub);
		render_floor_and_ceiling(img, cub, i);
	}
}

void		render_floor_and_ceiling(t_image *img, t_cub *cub, int ray_x)
{
	t_ray		*ray;
	t_rectangle	floor_rectangle;
	t_rectangle	ceiling_rectangle;

	ray = &cub->rays[ray_x];
	if (ray->normalized_wall_strip_height >= cub->window.height)
		return ;
	floor_rectangle.x = ray_x * WALL_STRIP_WIDTH;
	floor_rectangle.y = cub->window.height / 2
						+ ray->normalized_wall_strip_height / 2;
	floor_rectangle.width = WALL_STRIP_WIDTH;
	floor_rectangle.height = cub->window.height / 2
							- ray->normalized_wall_strip_height / 2;
	floor_rectangle.color = cub->colors[FLOOR].hexcode;
	ceiling_rectangle.x = ray_x * WALL_STRIP_WIDTH;
	ceiling_rectangle.y = 0;
	ceiling_rectangle.width = WALL_STRIP_WIDTH;
	ceiling_rectangle.height = cub->window.height / 2
							- ray->normalized_wall_strip_height / 2;
	ceiling_rectangle.color = cub->colors[CEILING].hexcode;
	put_rectangle(img, ceiling_rectangle);
	put_rectangle(img, floor_rectangle);
}

void		render_wall_strip(t_image *img, t_ray ray, int ray_x, t_cub *cub)
{
	t_texture_renderer	s;
	int					i;

	ray.texture = find_correct_texture(ray, cub);
	s.step_texture = ray.texture->height / ray.wall_strip_height;
	s.ratio_of_texture_to_appear = ray.normalized_wall_strip_height
									/ ray.wall_strip_height;
	s.texture_y = ((double)ray.texture->height / 2.0)
		- (s.ratio_of_texture_to_appear * (double)ray.texture->height / 2);
	s.texture_x = find_texture_x(ray, cub);
	i = -1;
	while (++i < (int)ray.normalized_wall_strip_height)
	{
		s.color = *(unsigned int *)(ray.texture->img.addr
					+ (int)s.texture_y * ray.texture->img.line_length
					+ (int)s.texture_x * (ray.texture->img.bits_per_pixel / 8));
		my_mlx_pixel_put(img, ray_x * WALL_STRIP_WIDTH
						, cub->window.height / 2
							- ray.normalized_wall_strip_height / 2 + i
						, s.color);
		s.texture_y += s.step_texture;
	}
}

t_texture	*find_correct_texture(t_ray ray, t_cub *cub)
{
	if (ray.is_ray_facing_right && ray.is_vertical_hit)
		return (&cub->textures[EA]);
	else if (!ray.is_ray_facing_right && ray.is_vertical_hit)
		return (&cub->textures[WE]);
	else if (ray.is_ray_facing_down && !ray.is_vertical_hit)
		return (&cub->textures[SO]);
	else if (!ray.is_ray_facing_down && !ray.is_vertical_hit)
		return (&cub->textures[NO]);
	return (NULL);
}
