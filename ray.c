#include "header.h"

t_ray rays[NUM_RAYS];

void	update_rays(void)
{
	double current_angle;

	current_angle = player.rotation_angle - FOV_ANGLE / 2;
	current_angle = normalize_angle(current_angle);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		rays[i].found_ver_wall_hit = 0;
		rays[i].found_hor_wall_hit = 0;
		rays[i].angle = normalize_angle(current_angle);
		rays[i].is_ray_facing_down = (rays[i].angle > 0 && rays[i].angle < M_PI);
		rays[i].is_ray_facing_right = (rays[i].angle < M_PI / 2 || rays[i].angle > 1.5 * M_PI);
		find_horizontal_intersection(&rays[i]);
		find_vertical_intersection(&rays[i]);
		select_shortest_wall_hit(&rays[i]);
		// printf("hor_wall_hit_x: %d, hor_wall_hit_y: %d\n", rays[i].hor_wall_hit_x, rays[i].hor_wall_hit_y);
		// printf("ver_wall_hit_x: %d, ver_wall_hit_y: %d\n", rays[i].ver_wall_hit_x, rays[i].ver_wall_hit_y);
		// printf("found: %d, player angle: %f, ray.angle: %f\n", rays[i].found_ver_wall_hit, player.rotation_angle, rays[i].angle);
		// printf("right: %d, player angle: %f, ray.angle: %f\n", rays[i].is_ray_facing_right, player.rotation_angle, rays[i].angle);
		current_angle += FOV_ANGLE / NUM_RAYS;
	}
}

void	select_shortest_wall_hit(t_ray *ray)
{
	double hor_distance = (ray->found_hor_wall_hit ?
							distanceBetween(player.x, player.y, ray->hor_wall_hit_x, ray->hor_wall_hit_y) :
							__DBL_MAX__);
	double ver_distance = (ray->found_ver_wall_hit ?
							distanceBetween(player.x, player.y, ray->ver_wall_hit_x, ray->ver_wall_hit_y) :
							__DBL_MAX__);
	ray->wall_hit_x = (hor_distance > ver_distance ? ray->ver_wall_hit_x : ray->hor_wall_hit_x);
	ray->wall_hit_y = (hor_distance > ver_distance ? ray->ver_wall_hit_y : ray->hor_wall_hit_y);
	ray->distance = (hor_distance > ver_distance ? ver_distance : hor_distance);
}



void find_vertical_intersection(t_ray *ray)
{
	int y_intercept, x_intercept;
	double ystep, xstep;

	x_intercept = (player.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += (ray->is_ray_facing_right ? TILE_SIZE : 0);

	y_intercept = player.y + (x_intercept - player.x) * tan(ray->angle);
	// ray->ver_wall_hit_x = x_intercept;
	// ray->ver_wall_hit_y = y_intercept;
	// printf("x: %d, y: %d\n", x_intercept, y_intercept);
	// return;

	xstep = (ray->is_ray_facing_right ? TILE_SIZE : -TILE_SIZE);
	ystep = TILE_SIZE * tan(ray->angle);
	ystep *= (!ray->is_ray_facing_down && ystep > 0 ? -1 : 1);
	ystep *= (ray->is_ray_facing_down && ystep < 0 ? -1 : 1);
	// printf("xstep: %f, ystep: %f\n", xstep, ystep);

	int nextVerTouchX = x_intercept;
	int nextVerTouchY = y_intercept;

	// if (!ray->is_ray_facing_right)
	// 	nextVerTouchX--;
	while (nextVerTouchY >= 0 && nextVerTouchY < WIN_HEIGHT && nextVerTouchX >= 0 && nextVerTouchX < WIN_WIDTH)
	{
		if (WallAt(nextVerTouchX - (!ray->is_ray_facing_right ? 1 : 0), nextVerTouchY))
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

void	find_horizontal_intersection(t_ray *ray)
{
	int y_intercept, x_intercept;
	double ystep, xstep;

	y_intercept = (player.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += (ray->is_ray_facing_down ? TILE_SIZE : 0);

	x_intercept = player.x + (y_intercept - player.y) / tan(ray->angle);
	// printf("x: %d, y: %d\n", x_intercept, y_intercept);

	ystep = (ray->is_ray_facing_down ? TILE_SIZE : -TILE_SIZE);
	xstep = TILE_SIZE / tan(ray->angle);
	xstep *= (ray->is_ray_facing_right && xstep < 0 ? -1 : 1);
	xstep *= (!ray->is_ray_facing_right && xstep > 0 ? -1 : 1);

	int nextHorTouchX = x_intercept;
	int nextHorTouchY = y_intercept;

	// if (!ray->is_ray_facing_down)
	// 	nextHorTouchY--;
	while (nextHorTouchY >= 0 && nextHorTouchY < WIN_HEIGHT && nextHorTouchX >= 0 && nextHorTouchX < WIN_WIDTH)
	{
		if (WallAt(nextHorTouchX, nextHorTouchY - (!ray->is_ray_facing_down ? 1 : 0)))
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

void	render_rays(t_data *img)
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		plot_line(img,
					MINIMAP_SCALE_FACTOR * player.x,
					MINIMAP_SCALE_FACTOR * player.y,
					MINIMAP_SCALE_FACTOR * rays[i].wall_hit_x,
					MINIMAP_SCALE_FACTOR * rays[i].wall_hit_y);
	}
	// for (int i = 0; i < NUM_RAYS; i++)
	// {
	// 	plot_line(img,
	// 				player.x,
	// 				player.y,
	// 				player.x + cos(rays[i].angle) * 20,
	// 				player.y + sin(rays[i].angle) * 20);
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

double distanceBetween(int x0, int y0, int x1, int y1)
{
	double distance;

	distance = sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
	return distance;
}

void	render3d(t_data *img)
{
	t_ray ray;
	double distanceProjectionPlane;
	double wallStripHeight;

	(void)img;
	for (int i = 0; i < NUM_RAYS; i++)
	{
		ray = rays[i];
		distanceProjectionPlane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
		wallStripHeight = (TILE_SIZE / ray.distance) * distanceProjectionPlane;
		wallStripHeight = normalize_wall_height(wallStripHeight);
		// printf("win_height: %d, projection plane: %f, rayDistance: %f, wallHeight: %f\n", WIN_HEIGHT, distanceProjectionPlane, ray.distance, wallStripHeight);
		put_rectangle_at(img, i * WALL_STRIP_WIDTH,
							WIN_HEIGHT / 2 - wallStripHeight / 2,
							WALL_STRIP_WIDTH,
							wallStripHeight,
							0X00FFFFFF);
	}
}

int normalize_wall_height(double height)
{
	if (height >= WIN_HEIGHT)
		return (WIN_HEIGHT);
	else
		return (int)height;
}
