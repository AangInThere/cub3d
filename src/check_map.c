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

	if (check_characters_and_player_in_map(map) != 0)
		return (1);
	i = -1;
	while (++i < map->height)
	{
		j = 0;
		row_length = ft_strlen(map->rows[i]);
		while (j < row_length)
		{
			if (is_an_edge(map, j, i) && map->rows[i][j] != WALL)
				return (2);
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
				return (1);
			if (ft_strchr(PLAYER_STRING, map->rows[i][j]))
			{
				if (found_player_position)
					return (2);
				found_player_position = TRUE;
			}
			j++;
		}
	}
	return (found_player_position == TRUE ? 0 : 3);
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
	if (x < 0 || x >= ft_strlen(map->rows[y]))
		return (FALSE);
	return (TRUE);
}
