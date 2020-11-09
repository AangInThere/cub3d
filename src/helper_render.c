#include "header.h"

int put_square(t_image *data, int x, int y, int size, int color)
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

int put_rectangle(t_image *data, t_rectangle rectangle)
{
	int a;
	int b;

	b = 0;
	while (b < rectangle.height)
	{
		a = 0;
		while (a < rectangle.width)
		{
			my_mlx_pixel_put(data, rectangle.x + a++, rectangle.y + b, rectangle.color);
		}
		b++;
	}
	return (1);
}


void my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
