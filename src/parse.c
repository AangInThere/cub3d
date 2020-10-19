#include "header.h"

int parse(t_cub *cub, char *filename)
{
	int	fd;

	//check filename and argv arguments before
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (1);
	if (parse_premap(fd, cub) != 0)
	{
		print_error("Could not parse premap\n");
		return (2);
	}

	if (parse_map(fd, cub) != 0)
	{
		print_error("Could not parse map\n");
		return (3);
	}
	if (load_textures(cub) != 0)
	{
		print_error("Could not load textures\n");
		return (4);
	}
	return (0);
}

void	print_error(char *error_msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
}
