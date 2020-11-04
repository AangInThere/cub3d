#include "header.h"
#define MAP_STRING "012 NSWE"
#define PLAYER_STRING "NSWE"

static t_direction directions[] = {
	{ 1, -1},
	{ 1,  0},
	{ 1,  1},
	{ 0, -1},
	{ 0,  1},
	{-1, -1},
	{-1,  0},
	{-1,  1}
};

int check_map(t_map *map)
{
	int	i;
	int row_length;
	int j;
	t_error error_code;

	//check if map is not in 2 parts(with an empty line in the middle of it, consider this an error)
	if ((error_code = check_characters_and_player_in_map(map)) != 0)
		return (error_code);
	i = -1;
	while (++i < map->height)
	{
		j = 0;
		row_length = ft_strlen(map->rows[i]);
		while (j < row_length)
		{
			if (is_an_edge(map, j, i) && map->rows[i][j] != WALL)
				return (MAP_IS_NOT_CLOSED);
			j++;
		}
	}
	return (0);
}

int	check_characters_and_player_in_map(t_map *map)
{
	int	i;
	int	row_length;
	int	j;
	int	found_player_position;

	found_player_position = FALSE;
	i = -1;
	while (++i < map->height)
	{
		j = 0;
		row_length = ft_strlen(map->rows[i]);
		while (j < row_length)
		{
			if (ft_strchr(MAP_STRING, map->rows[i][j]) == NULL)
				return (UNKNOWN_CHAR_IN_MAP);
			if (ft_strchr(PLAYER_STRING, map->rows[i][j]))
			{
				if (found_player_position)
					return (TWO_PLAYERS_IN_MAP);
				found_player_position = TRUE;
			}
			j++;
		}
	}
	return (found_player_position == TRUE ? 0 : PLAYER_NOT_FOUND_IN_MAP);
}

t_bool	is_an_edge(t_map *map, int x, int y)
{
	int i;

	if (map->rows[y][x] == SPACE)
		return (FALSE);
	i = 0;
	while (i < 8)
	{
		if (!is_inside_map(map, x + directions[i].dx, y + directions[i].dy) ||
			map->rows[y + directions[i].dy][x + directions[i].dx] == SPACE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool is_inside_map(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return (FALSE);
	if (x < 0 || x >= (int)ft_strlen(map->rows[y]))
		return (FALSE);
	return (TRUE);
}
