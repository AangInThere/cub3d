#include "header.h"

t_ray ray_array[NUM_RAYS];

void	update_rays(t_cub *cub)
{
	double current_angle;

	current_angle = cub->player.rotation_angle - FOV_ANGLE / 2;
	current_angle = normalize_angle(current_angle);
	for (int i = 0; i < cub->number_of_rays; i++)
	{
		cub->rays[i].found_ver_wall_hit = 0;
		cub->rays[i].found_hor_wall_hit = 0;
		cub->rays[i].angle = normalize_angle(current_angle);
		cub->rays[i].is_ray_facing_down = (cub->rays[i].angle > 0 && cub->rays[i].angle < M_PI);
		cub->rays[i].is_ray_facing_right = (cub->rays[i].angle < M_PI / 2 || cub->rays[i].angle > 1.5 * M_PI);
		find_horizontal_intersection(&cub->rays[i], cub);
		find_vertical_intersection(&cub->rays[i], cub);
		select_shortest_wall_hit(&cub->rays[i], cub);
		cub->rays[i].distance = cub->rays[i].distance * cos(cub->rays[i].angle - cub->player.rotation_angle);
		// printf("hor_wall_hit_x: %d, hor_wall_hit_y: %d\n", cub->rays[i].hor_wall_hit_x, cub->rays[i].hor_wall_hit_y);
		// printf("ver_wall_hit_x: %d, ver_wall_hit_y: %d\n", cub->rays[i].ver_wall_hit_x, cub->rays[i].ver_wall_hit_y);
		// printf("found: %d, player angle: %f, ray.angle: %f\n", cub->rays[i].found_ver_wall_hit, cub->player.rotation_angle, cub->rays[i].angle);
		// printf("right: %d, player angle: %f, ray.angle: %f\n", cub->rays[i].is_ray_facing_right, cub->player.rotation_angle, cub->rays[i].angle);
		current_angle += FOV_ANGLE / cub->number_of_rays;
	}
}

void	select_shortest_wall_hit(t_ray *ray, t_cub *cub)
{
	double hor_distance = (ray->found_hor_wall_hit ?
							distanceBetween(cub->player.x, cub->player.y, ray->hor_wall_hit_x, ray->hor_wall_hit_y) :
							__DBL_MAX__);
	double ver_distance = (ray->found_ver_wall_hit ?
							distanceBetween(cub->player.x, cub->player.y, ray->ver_wall_hit_x, ray->ver_wall_hit_y) :
							__DBL_MAX__);
	ray->wall_hit_x = (hor_distance > ver_distance ? ray->ver_wall_hit_x : ray->hor_wall_hit_x);
	ray->wall_hit_y = (hor_distance > ver_distance ? ray->ver_wall_hit_y : ray->hor_wall_hit_y);
	ray->distance = (hor_distance > ver_distance ? ver_distance : hor_distance);
	ray->is_vertical_hit = (hor_distance > ver_distance ? 1 : 0);
}



void find_vertical_intersection(t_ray *ray, t_cub *cub)
{
	double y_intercept, x_intercept;
	double ystep, xstep;

	x_intercept = ((int)((cub->player.x) /  cub->tile_size)) *  cub->tile_size;
	x_intercept += (ray->is_ray_facing_right ?  cub->tile_size : 0);

	y_intercept = cub->player.y + (x_intercept - cub->player.x) * tan(ray->angle);
	// printf("x: %d, y: %d\n", x_intercept, y_intercept);

	xstep = (ray->is_ray_facing_right ?  cub->tile_size : - cub->tile_size);
	ystep =  cub->tile_size * tan(ray->angle);
	ystep *= (!ray->is_ray_facing_down && ystep > 0 ? -1 : 1);
	ystep *= (ray->is_ray_facing_down && ystep < 0 ? -1 : 1);
	// printf("xstep: %f, ystep: %f\n", xstep, ystep);

	double nextVerTouchX = x_intercept;
	double nextVerTouchY = y_intercept;

	while (nextVerTouchY >= 0 && nextVerTouchY < cub->window.height && nextVerTouchX >= 0 && nextVerTouchX < cub->window.width)
	{
		if (WallAt((nextVerTouchX - (!ray->is_ray_facing_right ? 1 : 0)), nextVerTouchY, cub->map, cub))
		{
			ray->ver_wall_hit_x = nextVerTouchX;
			ray->ver_wall_hit_y = nextVerTouchY;
			ray->found_ver_wall_hit = 1;
			return;
		}
		else
		{
			nextVerTouchX += xstep;
			nextVerTouchY += ystep;
		}
	}
}

void	find_horizontal_intersection(t_ray *ray, t_cub * cub)
{
	double y_intercept, x_intercept;
	double ystep, xstep;

	y_intercept = ((int)(cub->player.y /  cub->tile_size)) *  cub->tile_size;
	y_intercept += (ray->is_ray_facing_down ?  cub->tile_size : 0);

	x_intercept = cub->player.x + (y_intercept - cub->player.y) / tan(ray->angle);
	// printf("x: %d, y: %d\n", x_intercept, y_intercept);

	ystep = (ray->is_ray_facing_down ?  cub->tile_size : - cub->tile_size);
	xstep =  cub->tile_size / tan(ray->angle);
	xstep *= (ray->is_ray_facing_right && xstep < 0 ? -1 : 1);
	xstep *= (!ray->is_ray_facing_right && xstep > 0 ? -1 : 1);

	double nextHorTouchX = x_intercept;
	double nextHorTouchY = y_intercept;

	while (nextHorTouchY >= 0 && nextHorTouchY < cub->window.height && nextHorTouchX >= 0 && nextHorTouchX < cub->window.width)
	{
		if (WallAt(nextHorTouchX, nextHorTouchY - (!ray->is_ray_facing_down ? 1 : 0), cub->map, cub))
		{
			ray->hor_wall_hit_x = nextHorTouchX;
			ray->hor_wall_hit_y = nextHorTouchY;
			ray->found_hor_wall_hit = 1;
			return ;
		}
		else
		{
			nextHorTouchX += xstep;
			nextHorTouchY += ystep;
		}
	}
}

void	render_rays(t_image *img, t_cub *cub)
{
	for (int i = 0; i < cub->number_of_rays; i++)
	{
		plot_line(img,
					MINIMAP_SCALE_FACTOR * cub->player.x,
					MINIMAP_SCALE_FACTOR * cub->player.y,
					MINIMAP_SCALE_FACTOR * cub->rays[i].wall_hit_x,
					MINIMAP_SCALE_FACTOR * cub->rays[i].wall_hit_y);
	}
	// for (int i = 0; i < NUM_RAYS; i++)
	// {
	// 	plot_line(img,
	// 				cub->player.x,
	// 				cub->player.y,
	// 				cub->player.x + cos(ray_array[i].angle) * 20,
	// 				cub->player.y + sin(ray_array[i].angle) * 20);
	// }
}

double	normalize_angle(double angle)
{
	while (angle > 2 * M_PI)
		angle -= (2 * M_PI);
	while (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

double distanceBetween(double x0, double y0, double x1, double y1)
{
	double distance;

	distance = sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
	return distance;
}

void	render3d(t_image *img, t_cub *cub)
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
		wallStripHeight = ( cub->tile_size / ray.distance) * distanceProjectionPlane;
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
	double wallStripHeight = ( cub->tile_size / ray.distance) * distanceProjectionPlane;
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

int find_texture_x(t_ray ray, t_cub *cub)
{
	int texture_x;
	double wall_hit;

	wall_hit = (ray.is_vertical_hit ? ray.wall_hit_y : ray.wall_hit_x);
	// printf("Wall_hit: %f\n", wall_hit);
	while (wall_hit >  cub->tile_size)
		wall_hit -=  cub->tile_size;
	texture_x = ((wall_hit /  cub->tile_size) * (double)cub->textures[0].width);
	// printf("texture_x: %d, wall_hit: %f, ratio: %f\n", texture_x, wall_hit, (double)texture_x / (double)texture.width);
	return (texture_x);
}

double normalize_wall_height(double height, t_cub *cub)
{
	if (height >= cub->window.height)
		return (cub->window.height);
	else
		return height;
}
