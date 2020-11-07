#include "header.h"

int parse(t_cub *cub, char *filename)
{
	mlx_get_screen_size(cub->mlx_ptr, &cub->window.width, &cub->window.height);
	if ((cub->fd_config_file = open(filename, O_RDONLY)) == -1)
		print_error_and_clean_exit("Could not open config file", cub);
	if (parse_premap(cub->fd_config_file, cub) != 0)
	{
		// print_error_and_clean_exit(NULL, cub);
		return (2);
	}
	if (parse_map(cub->fd_config_file, cub) != 0)
	{
		// print_error("Could not parse map");
		// print_error_and_clean_exit(NULL, cub);
		return (3);
	}
	if (load_textures(cub) != 0)
	{
		// print_error("Could not load textures");
		// print_error_and_clean_exit(NULL, cub);
		return (4);
	}
	return (0);
}

