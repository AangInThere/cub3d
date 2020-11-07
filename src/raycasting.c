/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:11:36 by aclose            #+#    #+#             */
/*   Updated: 2020/11/07 16:12:26 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_rays(t_cub *cub)
{
	int		i;
	double	current_angle;

	i = -1;
	current_angle = cub->player.rotation_angle - FOV_ANGLE / 2;
	while (++i < cub->number_of_rays)
	{
		cub->rays[i].found_ver_wall_hit = 0;
		cub->rays[i].found_hor_wall_hit = 0;
		cub->rays[i].angle = normalize_angle(current_angle);
		cub->rays[i].is_ray_facing_down =
			(cub->rays[i].angle > 0 && cub->rays[i].angle < M_PI);
		cub->rays[i].is_ray_facing_right =
			(cub->rays[i].angle < M_PI / 2 || cub->rays[i].angle > 1.5 * M_PI);
		find_horizontal_intersection(&cub->rays[i], cub);
		find_vertical_intersection(&cub->rays[i], cub);
		select_shortest_wall_hit(&cub->rays[i], cub);
		cub->rays[i].distance =
			cub->rays[i].distance
			* cos(cub->rays[i].angle - cub->player.rotation_angle);
		current_angle += FOV_ANGLE / cub->number_of_rays;
	}
}

void	find_vertical_intersection(t_ray *ray, t_cub *cub)
{
	t_intersection_finder s;

	vert_intersec_setup(ray, cub, &s);
	while (s.next_touch_y >= 0 && s.next_touch_y < cub->window.height
			&& s.next_touch_x >= 0 && s.next_touch_x < cub->window.width)
	{
		if (is_wall_at((s.next_touch_x - (!ray->is_ray_facing_right ? 1 : 0))
						, s.next_touch_y, cub->map, cub))
		{
			ray->ver_wall_hit_x = s.next_touch_x;
			ray->ver_wall_hit_y = s.next_touch_y;
			ray->found_ver_wall_hit = 1;
			return ;
		}
		else
		{
			s.next_touch_x += s.x_step;
			s.next_touch_y += s.y_step;
		}
	}
}

void	vert_intersec_setup(t_ray *ray, t_cub *cub, t_intersection_finder *s)
{
	s->x_intercept = ((int)((cub->player.x) / cub->tile_size)) * cub->tile_size;
	s->x_intercept += (ray->is_ray_facing_right ? cub->tile_size : 0);
	s->y_intercept = cub->player.y
						+ (s->x_intercept - cub->player.x) * tan(ray->angle);
	s->x_step = (ray->is_ray_facing_right ? cub->tile_size : -cub->tile_size);
	s->y_step = cub->tile_size * tan(ray->angle);
	s->y_step *= (!ray->is_ray_facing_down && s->y_step > 0 ? -1 : 1);
	s->y_step *= (ray->is_ray_facing_down && s->y_step < 0 ? -1 : 1);
	s->next_touch_x = s->x_intercept;
	s->next_touch_y = s->y_intercept;
}

void	find_horizontal_intersection(t_ray *ray, t_cub *cub)
{
	t_intersection_finder	s;

	hor_intersec_setup(ray, cub, &s);
	while (s.next_touch_y >= 0 && s.next_touch_y < cub->window.height
			&& s.next_touch_x >= 0 && s.next_touch_x < cub->window.width)
	{
		if (is_wall_at(s.next_touch_x
				, s.next_touch_y - (!ray->is_ray_facing_down ? 1 : 0)
				, cub->map, cub))
		{
			ray->hor_wall_hit_x = s.next_touch_x;
			ray->hor_wall_hit_y = s.next_touch_y;
			ray->found_hor_wall_hit = 1;
			return ;
		}
		else
		{
			s.next_touch_x += s.x_step;
			s.next_touch_y += s.y_step;
		}
	}
}

void	hor_intersec_setup(t_ray *ray, t_cub *cub, t_intersection_finder *s)
{
	s->y_intercept = ((int)(cub->player.y / cub->tile_size)) * cub->tile_size;
	s->y_intercept += (ray->is_ray_facing_down ? cub->tile_size : 0);
	s->x_intercept = cub->player.x
		+ (s->y_intercept - cub->player.y) / tan(ray->angle);
	s->y_step = (ray->is_ray_facing_down ? cub->tile_size : -cub->tile_size);
	s->x_step = cub->tile_size / tan(ray->angle);
	s->x_step *= (ray->is_ray_facing_right && s->x_step < 0 ? -1 : 1);
	s->x_step *= (!ray->is_ray_facing_right && s->x_step > 0 ? -1 : 1);
	s->next_touch_x = s->x_intercept;
	s->next_touch_y = s->y_intercept;
}
