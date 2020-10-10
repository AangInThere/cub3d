#include "header.h"

static char *identifier_textures[] = {"NO", "SO", "WE", "EA", "S"};

// int	parse_texture(char *line, t_texture *texture, void *mlx_ptr)
// {

// 	texture->img.img = mlx_xpm_file_to_image(mlx_ptr, "textures/eagle.xpm", &texture->width, &texture->height);
// 	texture->img.addr = mlx_get_data_addr(texture->img.img, &(texture->img.bits_per_pixel), &(texture->img.line_length),
// 										 &(texture->img.endian));
// }

int	check_formatting_texture(char *line)
{
	int	i;
	t_bool	has_a_match;

	i = 0;
	has_a_match = FALSE;
	while (i < 5)
	{
		if (ft_strncmp(line, identifier_textures[i], ft_strlen(identifier_textures[i])) == 0)
		{
			has_a_match = TRUE;
			line += ft_strlen(identifier_textures[i]);
			break;
		}
		i++;
	}
	if (!has_a_match || *line != ' ')
		return (-1);
	skip_spaces(&line);
	if (*line == '\0')
		return (-2);
	while (*line != ' ' && *line)
		line++;
	skip_spaces(&line);
	return (*line == '\0' ? 0 : -3);
}
