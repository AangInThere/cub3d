#include "header.h"

static char *g_error_msg[] = {
	[UNKNOWN_IDENTIFIER] = "Unknown identifier met in the config file",
	[SAME_IDENTIFIER_TWICE] = "Same identifier met two times in config file",
	[MALLOC_ERROR] = "Error met while allocating memory",
	[SMALLER_THAN_MINIMUM_RESOLUTION] = "The resolution specified is smaller than the mininum",
	[COLOR_PARSING] = "Could not parse color (numbers should be in the range [0, 255])",
	[MISSING_ELEMENTS] = "Not all necessary identifiers were present in config file",
	[CONFIG_FILE_READING] = "Error encountered when reading config file",
	[FORMATTING_TEXTURE] = "Formatting of textures is invalid",
	[FORMATTING_RESOLUTION] = "Formatting of resolution is invalid",
	[FORMATTING_COLOR] = "Formatting of colors is invalid",
	[UNKNOWN_CHAR_IN_MAP] = "Unknown char met in the map content",
	[TWO_PLAYERS_IN_MAP] = "Two players found in the map",
	[PLAYER_NOT_FOUND_IN_MAP] = "Player not found in the map",
	[MAP_IS_NOT_CLOSED] = "The map is not closed by walls",
	[EMPTY_LINE_IN_THE_MIDDLE] = "There is an empty line in the middle of the map content",
	[LOADING_TEXTURES] = "Could not load textures"
};

void print_error(char *error_msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}

int	free_and_destroy(t_cub *cub)
{
	int	i;

	if (cub->fd_config_file > 0)
		close(cub->fd_config_file);
	i = -1;
	if (cub->map.rows)
	{
		while (++i < cub->map.malloced_height)
			free(cub->map.rows[i]);
		free(cub->map.rows);
	}
	if (cub->rays)
		free(cub->rays);
	if (cub->map.sprites)
		free(cub->map.sprites);
	if (cub->images[0].img_ptr)
	{
		//maybe I will switch to only one image after so be careful about these lines
		mlx_destroy_image(cub->mlx_ptr, cub->images[0].img_ptr);
		mlx_destroy_image(cub->mlx_ptr, cub->images[1].img_ptr);
	}
	free_and_destroy_textures(cub);
	if (cub->window.win_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->window.win_ptr);
	// if (cub->mlx_ptr)
	// 	mlx_destroy_display(cub->mlx_ptr);
	return (0);
}

int	free_and_destroy_textures(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (cub->textures[i].filepath)
			free(cub->textures[i].filepath);
		if (cub->textures[i].img.img_ptr)
			mlx_destroy_image(cub->mlx_ptr, cub->textures[i].img.img_ptr);
	}
	return (0);
}


int	print_error_and_clean_exit(char *error_msg, t_cub *cub)
{
	if (error_msg == NULL)
		print_error(g_error_msg[cub->error_code]);
	else
		print_error(error_msg);
	free_and_destroy(cub);
	exit(EXIT_FAILURE);
}
