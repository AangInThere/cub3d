/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:10:29 by aclose            #+#    #+#             */
/*   Updated: 2020/10/13 01:16:32 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int parse_resolution(char *line, t_cub *cub)
{
	t_window	*window;
	int	asked_height;
	int	asked_width;

	window = &(cub->window);
	while (!ft_isdigit(*line))
		line++;
	asked_width = ft_atoi(line);
	skip_digits(&line);
	skip_spaces(&line);
	asked_height = ft_atoi(line);
	if (asked_width < MINIMUM_WIDTH || asked_height < MINIMUM_HEIGHT)
		return (-1);
	window->width = (asked_width > window->width ? window->width : asked_width);
	window->height = (asked_height > window->height ? window->height : asked_height);
	return (0);
}

int	check_formatting_resolution(char *line)
{
	if (*line++ != 'R' && *line++ != ' ')
		return (-1);
	skip_spaces(&line);
	if (!ft_isdigit(*line++))
		return (-2);
	skip_digits(&line);
	if (*line++ != ' ')
		return (-3);
	skip_spaces(&line);
	if (!ft_isdigit(*line++))
		return (-4);
	skip_digits(&line);
	skip_spaces(&line);
	if (*line != '\0')
		return (-5);
	return (0);
}
