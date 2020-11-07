#include "header.h"
#define WRITE_ERROR 1

int save_bmp_and_exit(t_cub *cub)
{
	int fd;
	int filesize;
	int pad;

	if ((fd = open("screenshot.bmp", O_WRONLY | O_TRUNC | O_CREAT | O_APPEND, 0664)) < 0)
		print_error_and_clean_exit("Could not open or create screenshot.bmp", cub);
	pad = (4 - (cub->window.width * 3) % 4) % 4;
	filesize = 54 + 3 * (cub->window.width + pad) * cub->window.height;
	if (write_bmp_header(cub, fd, filesize) == WRITE_ERROR || write_bmp_pixel(cub, fd, pad, &cub->image) == WRITE_ERROR)
	{
		close(fd);
		print_error_and_clean_exit("Could not write to screenchot.bmp", cub);
	}
	close(fd);
	free_and_destroy(cub);
	exit(EXIT_SUCCESS);
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
	if (write(fd, bmp_header, 54) < 54)
		return (WRITE_ERROR);
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
			if (write(fd, &color, 3) < 3)
				return (WRITE_ERROR);
			j++;
		}
		if (write(fd, "\0\0\0", pad) < 0)
			return (WRITE_ERROR);
	}
	return (0);
}


