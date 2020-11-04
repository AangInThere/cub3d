/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:10:29 by aclose            #+#    #+#             */
/*   Updated: 2020/11/03 16:02:19 by aclose           ###   ########.fr       */
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
		return (cub->error_code = SMALLER_THAN_MINIMUM_RESOLUTION);
	window->width = (asked_width > window->width ? window->width : asked_width);
	window->height = (asked_height > window->height ? window->height : asked_height);
	return (0);
}

int	check_formatting_resolution(char *line)
{
	if (*line++ != 'R' || *line++ != ' ')
		return (FORMATTING_RESOLUTION);
	skip_spaces(&line);
	if (!ft_isdigit(*line++))
		return (FORMATTING_RESOLUTION);
	skip_digits(&line);
	if (*line++ != ' ')
		return (FORMATTING_RESOLUTION);
	skip_spaces(&line);
	if (!ft_isdigit(*line++))
		return (FORMATTING_RESOLUTION);
	skip_digits(&line);
	skip_spaces(&line);
	if (*line != '\0')
		return (FORMATTING_RESOLUTION);
	return (0);
}
