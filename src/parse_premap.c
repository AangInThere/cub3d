#include "header.h"

static t_parser g_parser[] = {
	{"NO", parse_texture, check_formatting_texture, NORTH_TEXTURE},
	{"SO", parse_texture, check_formatting_texture, SOUTH_TEXTURE},
	{"WE", parse_texture, check_formatting_texture, WEST_TEXTURE},
	{"EA", parse_texture, check_formatting_texture, EAST_TEXTURE},
	{"S", parse_texture, check_formatting_texture, SPRITE_TEXTURE},
	{"R", parse_resolution, check_formatting_resolution, RESOLUTION},
	{"F", parse_color, check_formatting_color, FLOOR_COLOR},
	{"C", parse_color, check_formatting_color, CEILING_COLOR}};

int	parse_premap(int fd, t_cub *cub)
{
	char *line;
	int		gnl_ret;
	int		parse_one_line_ret;

	gnl_ret = get_next_line(fd, &line);
	while (gnl_ret > 0)
	{
		if (!is_empty_line(line))
		{
			if ((parse_one_line_ret = parse_one_line(line, cub)) != 0)
			{
				printf("parse_one_line return value when failed (%s): %d\n", line, parse_one_line_ret);
				free(line);
				return (1);
			}
		}
		free(line);
		if (each_element_of_premap_is_parsed(cub->already_parsed))
			return (0);
		gnl_ret = get_next_line(fd, &line);
	}
	return (2);
}

int	parse_one_line(char *line, t_cub *cub)
{
	int	i;
	t_bool has_a_match;

	has_a_match = FALSE;
	i = -1;
	skip_spaces(&line);
	while (++i < 8)
	{
		if (ft_strncmp(line, g_parser[i].identifier, ft_strlen(g_parser[i].identifier)) == 0)
		{
			has_a_match = TRUE;
			break;
		}
	}
	if (!has_a_match)
		return (1);
	if (g_parser[i].format_checking_function(line) != 0)
		return (2);
	if (cub->already_parsed & g_parser[i].parsing_code)
		return (3); //already parsed;
	if (g_parser[i].parsing_function(line, cub) != 0)
		return (4);
	cub->already_parsed |= g_parser[i].parsing_code;
	printf("Just succesfully parsed: %s\n", g_parser[i].identifier); //TO dELETE;
	return (0);
}

int each_element_of_premap_is_parsed(unsigned already_parsed)
{
	unsigned	everything_is_parsed;
	int i;

	everything_is_parsed = 0;
	i = 0;
	while (i < 8)
		everything_is_parsed |= g_parser[i++].parsing_code;
	if (already_parsed == everything_is_parsed)
		return (1);
	return (0);
}
