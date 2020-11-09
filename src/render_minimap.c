/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:43:30 by aclose            #+#    #+#             */
/*   Updated: 2020/11/10 00:50:20 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define PLAYER_COLOR 0XFF0000
#define MINIMAP_COLOR 0x0032CD32

void	render_minimap(t_image *data, t_cub *cub)
{
	int	j;
	int	square_size;
	int	i;

	square_size = cub->window.width / cub->map.width;
	if (square_size > cub->window.height / cub->map.height)
		square_size = cub->window.height / cub->map.height;
	square_size = (square_size * MINIMAP_SCALE_FACTOR);
	i = -1;
	while (++i < cub->map.height)
	{
		j = -1;
		while (++j < cub->map.row_lengths[i])
		{
			if (cub->map.rows[i][j] == WALL)
				put_square(data, j * square_size, i * square_size
							, square_size);
		}
	}
	render_player_on_minimap(data, cub, square_size);
}

void	render_player_on_minimap(t_image *img, t_cub *cub, int square_size)
{
	double	x;
	double	y;

	x = square_size * (cub->player.x / cub->tile_size);
	y = square_size * (cub->player.y / cub->tile_size);
	plot_circle(img, x, y, square_size / 2);
}

int		put_square(t_image *data, int x, int y, int size)
{
	int a;
	int b;

	b = 0;
	while (b < size)
	{
		a = 0;
		while (a < size)
		{
			my_mlx_pixel_put(data, x + a++, y + b, MINIMAP_COLOR);
		}
		b++;
	}
	return (1);
}

void	plot_circle(t_image *img, int xm, int ym, int r)
{
	int	x;
	int y;
	int	err;

	x = -r;
	y = 0;
	err = 2 - 2 * r;
	while (err == 2 - 2 * r || x < 0)
	{
		my_mlx_pixel_put(img, xm - x, ym + y, PLAYER_COLOR);
		my_mlx_pixel_put(img, xm - y, ym - x, PLAYER_COLOR);
		my_mlx_pixel_put(img, xm + x, ym - y, PLAYER_COLOR);
		my_mlx_pixel_put(img, xm + y, ym + x, PLAYER_COLOR);
		r = err;
		if (r > x)
			err += ++x * 2 + 1;
		if (r <= y)
			err += ++y * 2 + 1;
	}
}
