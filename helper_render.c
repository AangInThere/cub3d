#include "header.h"

void plot_line(t_data *data, int x0, int y0, int x1, int y1)
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

int put_square_at(t_data *data, int x, int y, int size, int color)
{
	int a;
	int b;

	b = 0;
	while (b < size)
	{
		a = 0;
		while (a < size)
		{
			my_mlx_pixel_put(data, x + a++, y + b, color);
		}
		b++;
	}
	return (1);
}

int put_rectangle_at(t_data *data, int x, int y, int width, int height, int color)
{
	int a;
	int b;

	b = 0;
	while (b < height)
	{
		a = 0;
		while (a < width)
		{
			my_mlx_pixel_put(data, x + a++, y + b, color);
		}
		b++;
	}
	return (1);
}

void render_grid(t_data *data)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (grid[i][j] == 1)
				put_square_at(data, j * 20, i * 20, 20, 0x0032CD32);
		}
	}
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
