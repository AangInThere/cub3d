#include "header.h"

// int current_imgnbr;
// t_image img1;
// t_image img2;
// t_texture texture;
// int grid[11][15] = {
// 	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
// 	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
// 	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
// 	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
// 	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
// 	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1 },
// 	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
// 	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
// 	{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 },
// 	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
// 	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
// };


int main(int argc, char **argv)
{
	// t_mlx	mlx;
	t_cub	cub;

	(void)argc;
	(void)argv;

	ft_bzero(&cub, sizeof(cub));
	cub.mlx_ptr = mlx_init();
	if (argc == 2)
	{
		if (check_file_name(argv[1]))
			printf("Error in filename\n");
		else
			printf("Filename is fine\n");
	}
	// mlx.mlx_ptr = mlx_init();
	mlx_get_screen_size(cub.mlx_ptr, &cub.window.width, &cub.window.height);
	if (parse(&cub, argv[1]) != 0)
		exit(0);
	set_up_window_and_images_for_cub(&cub);
	set_player_starting_position(&cub.player, cub.map, &cub);
	// mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	// img1.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	// img1.addr = mlx_get_data_addr(img1.img_ptr, &(img1.bits_per_pixel), &(img1.line_length),
	// 							 &(img1.endian));
	// img2.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	// img2.addr = mlx_get_data_addr(img2.img_ptr, &(img2.bits_per_pixel), &(img2.line_length),
	// 							 &(img2.endian));
	// texture.img.img_ptr = mlx_xpm_file_to_image(mlx.mlx_ptr, "textures/eagle.xpm", &texture.width, &texture.height);
	// texture.img.addr = mlx_get_data_addr(texture.img.img_ptr, &(texture.img.bits_per_pixel), &(texture.img.line_length),
	// 									 &(texture.img.endian));
	// //render_grid(&img);
	// // mlx_put_image_to_window(mlx.mlx_ptr, mlx_win, img.img, 0, 0);

	// mlx_hook(mlx.win_ptr, 2, 1L << 0, key_win, 0);
	// mlx_hook(mlx.win_ptr, 3, 1L << 1, key_release_win, 0);
	// mlx_hook(mlx.win_ptr, 17, 1L << 17, destroy_win, 0);
	// mlx_loop_hook(mlx.mlx_ptr, render_next_frame, &mlx);

	// mlx_loop(mlx.mlx_ptr);
	mlx_loop(cub.mlx_ptr);
}
