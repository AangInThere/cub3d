#include "header.h"

static char *g_identifier_colors[] = {"F", "C"};

int	parse_color(char *line, t_cub *cub)
{
	int i;

	i = 0;
	while (i < 2)
	{
		if (ft_strncmp(line, g_identifier_colors[i], ft_strlen(g_identifier_colors[i])) == 0)
		{
			line += ft_strlen(g_identifier_colors[i]);
			skip_spaces(&line);
			if (parse_color_numbers(line, &(cub->colors[i])))
				return (-1);
			break;
		}
		i++;
	}
	return (0);
}

int	parse_color_numbers(char *line, t_color *color)
{
	int	temp;

	temp = ft_atoi(line);
	if (temp > 255)
		return (-1);
	color->rgb.r = temp;
	skip_until_next_number(&line);
	temp = ft_atoi(line);
	if (temp > 255)
		return (-2);
	color->rgb.g = temp;
	skip_until_next_number(&line);
	temp = ft_atoi(line);
	if (temp > 255)
		return (-3);
	color->rgb.b = temp;
	return (0);
}

int	check_formatting_color(char *line)
{
	int	i;
	t_bool	has_a_match;

	i = -1;
	has_a_match = FALSE;
	while (++i < 2)
		if (ft_strncmp(line, g_identifier_colors[i], ft_strlen(g_identifier_colors[i])) == 0)
			has_a_match = TRUE;
	if (!has_a_match || *++line != ' ')
		return (-1);
	if (check_formatting_color_number(&line) != 0)
		return (-2);
	if (*line++ != ',')
		return (-3);
	if (check_formatting_color_number(&line) != 0)
		return (-4);
	if (*line++ != ',')
		return (-5);
	if (check_formatting_color_number(&line) != 0)
		return (-6);
	if (*line != '\0')
		return (-7);
	return (0);
}

int	check_formatting_color_number(char **line)
{
	int	number_of_digits_skipped;

	number_of_digits_skipped = 0;
	skip_spaces(line);
	while (ft_isdigit(**line))
	{
		(*line)++;
		number_of_digits_skipped++;
	}
	skip_spaces(line);
	if (number_of_digits_skipped > 3 || number_of_digits_skipped == 0)
		return (-1);
	return (0);
}

void skip_until_next_number(char **line)
{
	skip_digits(line);
	while (**line && !ft_isdigit(**line))
		(*line)++;
}
