/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:10:29 by aclose            #+#    #+#             */
/*   Updated: 2020/10/05 00:38:30 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_file_name(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		return (1);
	return (0);
}

int parse_resolution(char *line)
{
	line++;
	while (*line == ' ')
		line++;

}

int	check_formatting_resolution(char *line)
{
	if (*line++ != 'R' && *line++ != ' ')
		return (-1);
	while (*line == ' ')
		line++;
	if (!ft_isdigit(*line++))
		return (-1);
	while (ft_isdigit(*line))
		line++;
	if (*line++ != ' ')
		return (-1);
	while (*line == ' ')
		line++;
	if (!ft_isdigit(*line++))
		return (-1);
	while (ft_isdigit(*line))
		line++;
	while (*line == ' ')
		line++;
	if (*line != '\0')
		return (-1);
	return (0);
}
