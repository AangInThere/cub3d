#include "header.h"
#define INITIAL_HEIGHT 8

int parse_map(int fd, t_cub *cub)
{
	if (get_map_from_file(fd, &cub->map) != 0)
		return (cub->error_code = CONFIG_FILE_READING);
	if ((cub->error_code = check_map(&cub->map)) != 0)
		return (1);
	return (0);
}

int get_map_from_file(int fd, t_map *map)
{
	int	gnl_ret;
	char *line;

	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		gnl_ret = get_next_line(fd, &line);
		if (gnl_ret < 0)
			return (CONFIG_FILE_READING);
		if (map->height == 0 &&  is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (map->height >= map->malloced_height)
			realloc_map(map);
		map->rows[map->height] = line;
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		map->height++;
	}
	remove_empty_lines_at_the_end(map);
	// map->height = ft_compute_real_height(map);
	return (0);
}

char **realloc_map(t_map *map)
{
	char	**new_rows;
	int new_size;

	new_size = (map->malloced_height == 0 ? INITIAL_HEIGHT : map->malloced_height * 2);
	new_rows = ft_calloc(new_size,  sizeof(char *));
	ft_memcpy(new_rows, map->rows, map->malloced_height * sizeof(char *));
	map->malloced_height = new_size;
	free(map->rows);
	map->rows = new_rows;
	return (NULL);
}

// int	ft_compute_real_height(t_map *map)
// {
// 	int height;
// 	int i;

// 	i = 0;
// 	height = 0;
// 	while (i < map->height)
// 	{
// 		if (is_empty_line(map->rows[i]))
// 			break;
// 		height++;
// 		i++;
// 	}
// 	return (height);
// }

int remove_empty_lines_at_the_end(t_map *map)
{
	int	i;

	i = map->height - 1;
	while (i >= 0)
	{
		if (is_empty_line(map->rows[i]))
		{
			free(map->rows[i]);
			map->height--;
		}
		else
			break;
		i--;
	}
	return (0);
}
