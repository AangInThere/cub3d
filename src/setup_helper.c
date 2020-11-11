/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 00:28:47 by aclose            #+#    #+#             */
/*   Updated: 2020/11/11 13:16:39 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_compute_tile_size(t_cub *cub)
{
	int according_to_width;
	int according_to_height;

	according_to_width = cub->window.width / cub->map.width;
	according_to_height = cub->window.height / cub->map.height;
	if (according_to_width == 0 || according_to_height == 0)
		return (1);
	return (according_to_width < according_to_height ? according_to_width
													: according_to_height);
}

int	setup_hooks(t_cub *cub)
{
	mlx_hook(cub->window.win_ptr, 2, 1L << 0, key_win, cub);
	mlx_hook(cub->window.win_ptr, 3, 1L << 1, key_release_win, cub);
	mlx_hook(cub->window.win_ptr, 17, 1L << 17, destroy_win, cub);
	mlx_loop_hook(cub->mlx_ptr, render_next_frame, cub);
	return (0);
}
