#include "header.h"

int render_next_frame(t_cub *cub)
{
	// t_image img = (current_imgnbr == 0 ? img1 : img2);
	// current_imgnbr = (current_imgnbr == 0 ? 1 : 0);
	// // clear_img(&img);
	// update_player();
	// update_rays();
	// // plot_line(&img
	// // 			, player.x
	// // 			, player.y
	// // 			, player.x + cos(player.rotation_angle) * 20
	// // 			, player.y + sin(player.rotation_angle) * 20);
	// render3d(&img);
	// render_player(&img);
	// render_grid(&img);
	// render_rays(&img);
	// mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img.img_ptr, 0, 0);
	// // mlx_put_image_to_window(mlx, mlx_win, texture.img.img, 0, 0);
	// return (1);
	t_image *img = &cub->images[cub->current_image];
	cub->current_image = (cub->current_image == 0 ? 1 : 0);
	update_player(cub);
	// printf("player.x: %f, player.y: %f\n", cub->player.x, cub->player.y);
	// printf("dir.x: %d, dir.y: %d\n", cub->player.dir_hor, cub->player.dir_ver);
	update_rays(cub);
	// clear_img(img, cub);

	render3d(img, cub);
	render_player(img, cub);
	render_grid(img, cub);
	// render_rays(img, cub);

	mlx_put_image_to_window(cub->mlx_ptr, cub->window.win_ptr, img->img_ptr, 0, 0);
	return 0;
}

void render3d(t_image *img, t_cub *cub)
{
	t_ray ray;
	double distanceProjectionPlane;
	double wallStripHeight;
	// int wall_bottom;
	// double step_texture;
	// double text_pos;
	// double correcteddWallDistance;

	(void)img;
	for (int i = 0; i < cub->number_of_rays; i++)
	{
		ray = cub->rays[i];
		distanceProjectionPlane = (cub->window.width / 2) / tan(FOV_ANGLE / 2);
		// correcteddWallDistance = ray.distance * cos(ray.angle - cub->player.rotation_angle);
		wallStripHeight = (cub->tile_size / ray.distance) * distanceProjectionPlane;
		// step_texture = texture.height / wallStripHeight;
		// text_pos = ((cub->window.height / 2 - normalize_wall_height(wallStripHeight)) - cub->window.height / 2 + wallStripHeight / 2) * step_texture;
		wallStripHeight = normalize_wall_height(wallStripHeight, cub);
		render_ray(img, cub->rays[i], i, cub);
		// wall_bottom = cub->window.height / 2 + wallStripHeight / 2;
		if (wallStripHeight < cub->window.height)
		{
			put_rectangle_at(img, i * WALL_STRIP_WIDTH,
							 0,
							 WALL_STRIP_WIDTH,
							 cub->window.height / 2 - wallStripHeight / 2,
							 cub->colors[CEILING].hexcode);
			put_rectangle_at(img, i * WALL_STRIP_WIDTH,
							 cub->window.height / 2 + wallStripHeight / 2,
							 WALL_STRIP_WIDTH,
							 cub->window.height / 2 - wallStripHeight / 2,
							 cub->colors[FLOOR].hexcode);
		}

		// printf("texture_x: %d, texture_width: %d, ratio: %f", texture_x, texture.width, (double)texture_x / (double)texture.width);
		// printf("cub->window.height: %d, projection plane: %f, rayDistance: %f, wallHeight: %f\n", cub->window.height, distanceProjectionPlane, correcteddWallDistance, wallStripHeight);
		// put_rectangle_at(img, i * WALL_STRIP_WIDTH,
		// 					cub->window.height / 2 - wallStripHeight / 2,
		// 					WALL_STRIP_WIDTH,
		// 					wallStripHeight,
		// 					0X00808080);
	}
}

void render_ray(t_image *img, t_ray ray, int ray_x, t_cub *cub)
{
	unsigned int color;
	int texture_y;
	double text_pos;

	double distanceProjectionPlane = (cub->window.width / 2) / tan(FOV_ANGLE / 2);
	double wallStripHeight = (cub->tile_size / ray.distance) * distanceProjectionPlane;
	double step_texture = cub->textures[0].height / wallStripHeight;
	// double text_pos = ((cub->window.height / 2 - normalize_wall_height(wallStripHeight)) - cub->window.height / 2 + wallStripHeight / 2) * step_texture;
	if (wallStripHeight == normalize_wall_height(wallStripHeight, cub))
		text_pos = 0;
	else
	{
		double ratio_of_texture_to_appear = normalize_wall_height(wallStripHeight, cub) / wallStripHeight;
		text_pos = ((double)cub->textures[0].height / 2.0) - (ratio_of_texture_to_appear * (double)cub->textures[0].height / 2);
	}
	wallStripHeight = normalize_wall_height(wallStripHeight, cub);
	int texture_x = find_texture_x(ray, cub);
	for (int i = 0; i < (int)wallStripHeight; i++)
	{
		texture_y = (int)text_pos;
		color = *(unsigned int *)(cub->textures[0].img.addr + texture_y * cub->textures[0].img.line_length + texture_x * (cub->textures[0].img.bits_per_pixel / 8));
		my_mlx_pixel_put(img, ray_x * WALL_STRIP_WIDTH, cub->window.height / 2 - wallStripHeight / 2 + i, color);
		text_pos += step_texture;
	}
}
