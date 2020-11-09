#include "header.h"

void render_minimap(t_image *data, t_cub *cub)
{
	int j;
	int square_size;

	square_size = cub->window.width / cub->map.width;
	if (square_size > cub->window.height / cub->map.height)
		square_size = cub->window.height / cub->map.height;
	square_size = (square_size * MINIMAP_SCALE_FACTOR);
	for (int i = 0; i < cub->map.height; i++)
	{
		for (j = 0; j < (int)ft_strlen(cub->map.rows[i]); j++)
		{
			if (cub->map.rows[i][j] == WALL)
				put_square(data, j * square_size, i * square_size, square_size, 0x0032CD32);
		}
	}
	render_player_on_minimap(data, cub, square_size);
}

void	render_player_on_minimap(t_image *img, t_cub *cub, int square_size)
{
	double	x;
	double	y;
	double	dx;
	double	dy;

	x = square_size * (cub->player.x / cub->tile_size);
	y = square_size * (cub->player.y / cub->tile_size);
	dx = cos(cub->player.rotation_angle) * square_size;
	dy = sin(cub->player.rotation_angle) * square_size;
	plot_circle(img, x, y, square_size / 2, 0X00FF0000);
	plot_line(img, x, y, x + dx, y + dy);
}

void plot_line(t_image *data, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */

	for (;;)
	{ /* loop */
		my_mlx_pixel_put(data, x0, y0, 0X00FFFFFF);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		} /* e_xy+e_x > 0 */
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		} /* e_xy+e_y < 0 */
	}
}

void plot_circle(t_image *img, int xm, int ym, int r, unsigned color)
{
	int x = -r, y = 0, err = 2 - 2 * r; /* II. Quadrant */
	do
	{
		my_mlx_pixel_put(img, xm - x, ym + y, color); /*   I. Quadrant */
		my_mlx_pixel_put(img, xm - y, ym - x, color); /*  II. Quadrant */
		my_mlx_pixel_put(img, xm + x, ym - y, color); /* III. Quadrant */
		my_mlx_pixel_put(img, xm + y, ym + x, color); /*  IV. Quadrant */
		r = err;
		if (r > x)
			err += ++x * 2 + 1; /* e_xy+e_x > 0 */
		if (r <= y)
			err += ++y * 2 + 1; /* e_xy+e_y < 0 */
	} while (x < 0);
}
