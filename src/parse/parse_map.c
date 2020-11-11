/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:02:48 by aclose            #+#    #+#             */
/*   Updated: 2020/11/11 12:40:40 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define INITIAL_HEIGHT 8

int		parse_map(int fd, t_cub *cub)
{
	if (get_map_from_file(fd, &cub->map) != 0)
		return (cub->error_code = CONFIG_FILE_READING);
	if ((cub->error_code = check_map(&cub->map)) != 0)
		return (1);
	if (populate_row_lengths(&cub->map) != 0)
		return (cub->error_code = MALLOC_ERROR);
	return (0);
}

int		populate_row_lengths(t_map *map)
{
	int	i;

	if ((map->row_lengths = malloc(sizeof(int) * map->height)) == NULL)
		return (MALLOC_ERROR);
	i = 0;
	while (i < map->height)
	{
		map->row_lengths[i] = ft_strlen(map->rows[i]);
		i++;
	}
	return (0);
}

int		get_map_from_file(int fd, t_map *map)
{
	int		gnl_ret;
	char	*line;

	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		gnl_ret = get_next_line(fd, &line);
		if (gnl_ret < 0)
			return (CONFIG_FILE_READING);
		if (map->height == 0 && is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (map->height >= map->malloced_height)
			if (realloc_map(map) == NULL)
				return (MALLOC_ERROR);
		map->rows[map->height] = line;
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		map->height++;
	}
	remove_empty_lines_at_the_end(map);
	return (0);
}

char	**realloc_map(t_map *map)
{
	char	**new_rows;
	int		new_size;

	new_size = (map->malloced_height == 0 ? INITIAL_HEIGHT
											: map->malloced_height * 2);
	if ((new_rows = ft_calloc(new_size, sizeof(char *))) == NULL)
		return (NULL);
	ft_memcpy(new_rows, map->rows, map->malloced_height * sizeof(char *));
	map->malloced_height = new_size;
	free(map->rows);
	map->rows = new_rows;
	return (map->rows);
}

int		remove_empty_lines_at_the_end(t_map *map)
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
			break ;
		i--;
	}
	return (0);
}
