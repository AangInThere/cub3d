#include "header.h"
#define INITIAL_HEIGHT 8

int parse_map(int fd, t_cub *cub)
{
	return 0;
}

int get_map_from_file(int fd, t_map *map)
{
	int	gnl_ret;
	char *line;

	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		gnl_ret = get_next_line(fd, &line);
		if (map->height == 0 &&  is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (map->height >= map->malloced_height)
			realloc_map(map);
		map->rows[map->height] = line;
		map->height++;
	}
	return 0;
}

char **realloc_map(t_map *map)
{
	char	**new_rows;
	int new_size;

	new_size = (map->malloced_height == 0 ? INITIAL_HEIGHT : map->malloced_height * 2);
	new_rows = malloc(sizeof(char *) * new_size);
	ft_memcpy(new_rows, map->rows, map->malloced_height * sizeof(char *));
	map->malloced_height = new_size;
	free(map->rows);
	map->rows = new_rows;
	return (NULL);
}
