#include "header.h"

t_bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (FALSE);
		line++;
	}
	return (TRUE);
}

char	*delete_leading_spaces(char *line)
{
	int	i;
	int	j;
	char	*result;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (i == 0)
		return (line);
	if (!(result = malloc(ft_strlen(line) - i + 1)))
		return (NULL);
	j = 0;
	while (line[i + j])
	{
		result[j] = line[i + j];
		j++;
	}
	result[j] = '\0';
	free(line);
	return (result);
}

void skip_spaces(char **line)
{
	while (**line == ' ')
		((*line)++);
}

void skip_digits(char **line)
{
	while (ft_isdigit(**line))
		((*line)++);
}

int	check_file_name(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		return (1);
	return (0);
}


