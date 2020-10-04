/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:10:29 by aclose            #+#    #+#             */
/*   Updated: 2020/09/29 16:16:17 by aclose           ###   ########.fr       */
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
