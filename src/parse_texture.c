#include "header.h"

static char *g_identifier_textures[] = {"NO", "SO", "WE", "EA", "S"};

int	parse_texture(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (ft_strncmp(line, g_identifier_textures[i], ft_strlen(g_identifier_textures[i])) == 0)
		{
			line += ft_strlen(g_identifier_textures[i]);
			skip_spaces(&line);
			if (!(cub->textures[i].filepath = ft_strdup(line)))
				return (-1);
			break;
		}
		i++;
	}
	return (0);
}

int	check_formatting_texture(char *line)
{
	int	i;
	t_bool	has_a_match;

	i = 0;
	has_a_match = FALSE;
	while (i < 5)
	{
		if (ft_strncmp(line, g_identifier_textures[i], ft_strlen(g_identifier_textures[i])) == 0)
		{
			has_a_match = TRUE;
			line += ft_strlen(g_identifier_textures[i]);
			break;
		}
		i++;
	}
	if (!has_a_match || *line != ' ')
		return (-1);
	skip_spaces(&line);
	if (*line == '\0')
		return (-2);
	return (0);
}
