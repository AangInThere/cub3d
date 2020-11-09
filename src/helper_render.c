/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:39:44 by aclose            #+#    #+#             */
/*   Updated: 2020/11/10 00:34:53 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			put_rectangle(t_image *data, t_rectangle rectangle)
{
	int a;
	int b;

	b = 0;
	while (b < rectangle.height)
	{
		a = 0;
		while (a < rectangle.width)
		{
			my_mlx_pixel_put(data, rectangle.x + a++
							, rectangle.y + b, rectangle.color);
		}
		b++;
	}
	return (1);
}

void		my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned	get_color_from_texture(t_texture *texture, t_sprite *sprite
									, double current_x, double current_y)
{
	unsigned	color;

	sprite->tex_x = (current_x - sprite->initial_x)
						* texture->width / sprite->width;
	sprite->tex_y = (current_y - sprite->initial_y)
						* texture->height / sprite->height;
	color = *(unsigned *)(texture->img.addr
				+ (int)sprite->tex_y * texture->img.line_length
				+ (int)sprite->tex_x * (texture->img.bits_per_pixel / 8));
	return (color);
}
