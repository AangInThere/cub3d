#include "header.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2 || argc > 3 || check_file_name(argv[1]) != 0 || (argc == 3 && ft_strcmp(argv[2], "--save") != 0))
	{
		ft_putstr_fd("Error/nUsage: ./cub3D *.cub [--save]\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_bzero(&cub, sizeof(cub));
	if ((cub.mlx_ptr = mlx_init()) == NULL)
		exit(EXIT_FAILURE);
	if (parse(&cub, argv[1]) != 0)
		print_error_and_clean_exit(NULL, &cub);
	if (setup_cub3d(&cub) != 0)
		print_error_and_clean_exit(NULL, &cub);
	// setup_window_and_images_for_cub(&cub);
	// set_player_starting_position(&cub.player, cub.map, &cub);
	// setup_sprites(&cub);
	mlx_loop(cub.mlx_ptr);
}
