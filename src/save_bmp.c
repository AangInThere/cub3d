#include "header.h"

int save_bmp(t_cub *cub)
{
	int fd = open("screenshot.bmp", O_WRONLY | O_TRUNC | O_CREAT | O_APPEND);
	int filesize;
	int pad;

	pad = (4 - (cub->window.width * 3) % 4) % 4;
	filesize = 54 + 3 * (cub->window.width + pad) * cub->window.height;
	write_bmp_header(cub, fd, filesize);
	write_bmp_pixel(cub, fd, pad, &cub->image);
	close(fd);
	return (0);
}

int write_bmp_header(t_cub *cub, int fd, int filesize)
{
	unsigned char bmp_header[54];


	ft_bzero(bmp_header, 54);
	ft_memcpy(bmp_header, "BM", 2);
	ft_memcpy(bmp_header + 2, &filesize, 4);
	bmp_header[10] = 54;
	bmp_header[14] = 40;
	ft_memcpy(bmp_header + 18, &cub->window.width, 4);
	ft_memcpy(bmp_header + 22, &cub->window.height, 4);
	bmp_header[26] = 1;
	bmp_header[28] = 24;
	write(fd, bmp_header, 54);
	return (0);
}

int write_bmp_pixel(t_cub *cub, int fd, int pad, t_image *image)
{
	int	i;
	int j;
	unsigned color;

	i = cub->window.height;
	while (--i >= 0)
	{
		j = 0;
		while (j < cub->window.width)
		{
			color = *(unsigned int *)(image->addr + i * image->line_length + j * (image->bits_per_pixel / 8));
			write(fd, &color, 3);
			j++;
		}
		write(fd, "\0\0\0", pad);
	}
	return (0);
}


