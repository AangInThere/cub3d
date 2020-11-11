/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:55:27 by aclose            #+#    #+#             */
/*   Updated: 2020/11/11 12:24:30 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2 || argc > 3 || check_file_name(argv[1]) != 0
			|| (argc == 3 && ft_strcmp(argv[2], "--save") != 0))
	{
		ft_putstr_fd("Error\nUsage: ./cub3D *.cub [--save]\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_bzero(&cub, sizeof(cub));
	if (argc == 3)
		cub.should_save_first_frame = TRUE;
	if ((cub.mlx_ptr = mlx_init()) == NULL)
		exit(EXIT_FAILURE);
	if (parse(&cub, argv[1]) != 0)
		print_error_and_clean_exit(NULL, &cub);
	if (setup_cub3d(&cub) != 0)
		print_error_and_clean_exit(NULL, &cub);
	mlx_loop(cub.mlx_ptr);
}
