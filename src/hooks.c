/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:40:51 by aclose            #+#    #+#             */
/*   Updated: 2020/11/09 16:40:52 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define RIGHT_ARROW 65363
#define LEFT_ARROW 65361
#define KEY_ESC 65307

int	key_win(int key, t_cub *cub)
{
	if (key == KEY_ESC)
	{
		free_and_destroy(cub);
		exit(EXIT_SUCCESS);
	}
	else if (key == KEY_W)
		cub->player.dir_ver = 1;
	else if (key == KEY_S)
		cub->player.dir_ver = -1;
	else if (key == KEY_A)
		cub->player.dir_hor = -1;
	else if (key == KEY_D)
		cub->player.dir_hor = 1;
	else if (key == LEFT_ARROW)
		cub->player.turn_dir = -1;
	else if (key == RIGHT_ARROW)
		cub->player.turn_dir = 1;
	return (0);
}

int	key_release_win(int key, t_cub *cub)
{
	if (key == KEY_W)
		cub->player.dir_ver = 0;
	else if (key == KEY_S)
		cub->player.dir_ver = 0;
	else if (key == KEY_A)
		cub->player.dir_hor = 0;
	else if (key == KEY_D)
		cub->player.dir_hor = 0;
	else if (key == LEFT_ARROW)
		cub->player.turn_dir = 0;
	else if (key == RIGHT_ARROW)
		cub->player.turn_dir = 0;
	return (0);
}

int	destroy_win(t_cub *cub)
{
	free_and_destroy(cub);
	exit(EXIT_SUCCESS);
}
