#include "header.h"

// t_ray ray_array[NUM_RAYS];

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

int find_texture_x(t_ray ray, t_cub *cub)
{
	int texture_x;
	double wall_hit;

	wall_hit = (ray.is_vertical_hit ? ray.wall_hit_y : ray.wall_hit_x);
	// printf("Wall_hit: %f\n", wall_hit);
	while (wall_hit >  cub->tile_size)
		wall_hit -=  cub->tile_size;
	texture_x = ((wall_hit /  cub->tile_size) * (double)ray.texture->width);
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
