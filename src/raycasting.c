#include "header.h"

void update_rays(t_cub *cub)
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
void find_vertical_intersection(t_ray *ray, t_cub *cub)
{
	double y_intercept, x_intercept;
	double ystep, xstep;

	x_intercept = ((int)((cub->player.x) / cub->tile_size)) * cub->tile_size;
	x_intercept += (ray->is_ray_facing_right ? cub->tile_size : 0);

	y_intercept = cub->player.y + (x_intercept - cub->player.x) * tan(ray->angle);
	// printf("x: %d, y: %d\n", x_intercept, y_intercept);

	xstep = (ray->is_ray_facing_right ? cub->tile_size : -cub->tile_size);
	ystep = cub->tile_size * tan(ray->angle);
	ystep *= (!ray->is_ray_facing_down && ystep > 0 ? -1 : 1);
	ystep *= (ray->is_ray_facing_down && ystep < 0 ? -1 : 1);
	// printf("xstep: %f, ystep: %f\n", xstep, ystep);

	double nextVerTouchX = x_intercept;
	double nextVerTouchY = y_intercept;

	while (nextVerTouchY >= 0 && nextVerTouchY < cub->window.height && nextVerTouchX >= 0 && nextVerTouchX < cub->window.width)
	{
		if (is_wall_at((nextVerTouchX - (!ray->is_ray_facing_right ? 1 : 0)), nextVerTouchY, cub->map, cub))
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
void find_horizontal_intersection(t_ray *ray, t_cub *cub)
{
	double y_intercept, x_intercept;
	double ystep, xstep;

	y_intercept = ((int)(cub->player.y / cub->tile_size)) * cub->tile_size;
	y_intercept += (ray->is_ray_facing_down ? cub->tile_size : 0);

	x_intercept = cub->player.x + (y_intercept - cub->player.y) / tan(ray->angle);
	// printf("x: %d, y: %d\n", x_intercept, y_intercept);

	ystep = (ray->is_ray_facing_down ? cub->tile_size : -cub->tile_size);
	xstep = cub->tile_size / tan(ray->angle);
	xstep *= (ray->is_ray_facing_right && xstep < 0 ? -1 : 1);
	xstep *= (!ray->is_ray_facing_right && xstep > 0 ? -1 : 1);

	double nextHorTouchX = x_intercept;
	double nextHorTouchY = y_intercept;

	while (nextHorTouchY >= 0 && nextHorTouchY < cub->window.height && nextHorTouchX >= 0 && nextHorTouchX < cub->window.width)
	{
		if (is_wall_at(nextHorTouchX, nextHorTouchY - (!ray->is_ray_facing_down ? 1 : 0), cub->map, cub))
		{
			ray->hor_wall_hit_x = nextHorTouchX;
			ray->hor_wall_hit_y = nextHorTouchY;
			ray->found_hor_wall_hit = 1;
			return;
		}
		else
		{
			nextHorTouchX += xstep;
			nextHorTouchY += ystep;
		}
	}
}
