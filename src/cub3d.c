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

int key_win(int key, t_cub *cub)
{
	(void)cub;
	printf("Key in Win1 : %d\n", key);
	if (key == 0xFF1B)
		exit(0);
	else if (key == 119)
		cub->player.dir_ver = 1;
	else if (key == 115)
		cub->player.dir_ver = -1;
	else if (key == 97)
		cub->player.dir_hor = -1;
	else if (key == 100)
		cub->player.dir_hor = 1;
	else if (key == 65361)
		cub->player.turn_dir = -1;
	else if (key == 65363)
		cub->player.turn_dir = 1;
	return 1;
}

int key_release_win(int key, t_cub *cub)
{
	(void)cub;
	printf("Key Release in Win1 : %d\n", key);
	if (key == 119)
		cub->player.dir_ver = 0;
	else if (key == 115)
		cub->player.dir_ver = 0;
	else if (key == 97)
		cub->player.dir_hor = 0;
	else if (key == 100)
		cub->player.dir_hor = 0;
	else if (key == 65361)
		cub->player.turn_dir = 0;
	else if (key == 65363)
		cub->player.turn_dir = 0;
	return 1;

}

int clear_img(t_image* img, t_cub *cub)
{
	for (int i = 0; i < cub->window.width; i++)
	{
		for (int j = 0; j < cub->window.height; j++)
		{
			my_mlx_pixel_put(img, i, j, 0X00000000);
		}
	}
	return 1;
}

int render_next_frame(t_cub *cub)
{
	// t_image img = (current_imgnbr == 0 ? img1 : img2);
	// current_imgnbr = (current_imgnbr == 0 ? 1 : 0);
	// // clear_img(&img);
	// update_player();
	// update_rays();
	// // plot_line(&img
	// // 			, player.x
	// // 			, player.y
	// // 			, player.x + cos(player.rotation_angle) * 20
	// // 			, player.y + sin(player.rotation_angle) * 20);
	// render3d(&img);
	// render_player(&img);
	// render_grid(&img);
	// render_rays(&img);
	// mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img.img_ptr, 0, 0);
	// // mlx_put_image_to_window(mlx, mlx_win, texture.img.img, 0, 0);
	// return (1);
	t_image *img = &cub->images[cub->current_image];
	cub->current_image = (cub->current_image == 0 ? 1 : 0);
	update_player(cub);
	// printf("player.x: %f, player.y: %f\n", cub->player.x, cub->player.y);
	// printf("dir.x: %d, dir.y: %d\n", cub->player.dir_hor, cub->player.dir_ver);
	update_rays(cub);
	clear_img(img, cub);

	render3d(img, cub);
	render_player(img, cub);
	render_grid(img, cub);
	// render_rays(img, cub);

	mlx_put_image_to_window(cub->mlx_ptr, cub->window.win_ptr, img->img_ptr, 0, 0);
	return 0;
}


int destroy_win(t_cub *cub)
{
	(void)cub;
	exit(0);
}

int ft_compute_tile_size(t_cub *cub)
{
	int according_to_width;
	int according_to_height;

	according_to_width = cub->window.width / cub->map.width;
	according_to_height = cub->window.height / cub->map.height;
	return (according_to_width < according_to_height ? according_to_width : according_to_height);
}

int set_up_window_and_images_for_cub(t_cub *cub)
{
	cub->window.win_ptr = mlx_new_window(cub->mlx_ptr, cub->window.width, cub->window.height, "Cub3D");
	cub->images[0].img_ptr = mlx_new_image(cub->mlx_ptr, cub->window.width, cub->window.height);
	cub->images[1].img_ptr = mlx_new_image(cub->mlx_ptr, cub->window.width, cub->window.height);
	cub->images[0].addr = mlx_get_data_addr(cub->images[0].img_ptr, &(cub->images[0].bits_per_pixel), &(cub->images[0].line_length),
								 &(cub->images[0].endian));
	cub->images[1].addr = mlx_get_data_addr(cub->images[1].img_ptr, &(cub->images[1].bits_per_pixel), &(cub->images[1].line_length),
								 &(cub->images[1].endian));
	mlx_hook(cub->window.win_ptr, 2, 1L << 0, key_win, cub);
	mlx_hook(cub->window.win_ptr, 3, 1L << 1, key_release_win, cub);
	mlx_hook(cub->window.win_ptr, 17, 1L << 17, destroy_win, cub);
	mlx_loop_hook(cub->mlx_ptr, render_next_frame, cub);
	cub->number_of_rays = cub->window.width / WALL_STRIP_WIDTH;
	cub->rays = malloc(sizeof(t_ray) * (cub->number_of_rays));
	cub->tile_size = ft_compute_tile_size(cub);
	cub->tile_width = cub->window.width / cub->map.width;
	cub->tile_height = cub->window.height / cub->map.height;

	return 0;
}

int set_player_starting_position(t_player *player, t_map map, t_cub *cub)
{
	char *player_string = "NSWE";
	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < (int)ft_strlen(map.rows[i]); j++)
		{
			if (ft_strchr(player_string, map.rows[i][j]) != NULL)
			{
				player->x = j * cub->tile_size + cub->tile_size / 2;
				player->y = i * cub->tile_size + cub->tile_size / 2;
				break;
			}
		}
	}
	return (0);
}

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


// int color_map(void * mlx, unsigned char *data, int bpp, int sl, int w, int h, int endian, int type)
// {
// 	int x;
// 	int y;
// 	int opp;
// 	int dec;
// 	int color;
// 	int color2;
// 	unsigned char *ptr;

// 	opp = bpp / 8;
// 	printf("(opp : %d) ", opp);
// 	y = h;
// 	while (y--)
// 	{
// 		ptr = data + y * sl;
// 		x = w;
// 		while (x--)
// 		{
// 			if (type == 2)
// 				color = (y * 255) / w + ((((w - x) * 255) / w) << 16) + (((y * 255) / h) << 8);
// 			else
// 				color = (x * 255) / w + ((((w - x) * 255) / w) << 16) + (((y * 255) / h) << 8);
// 			color2 = mlx_get_color_value(mlx, color);
// 			dec = opp;
// 			while (dec--)
// 				*(ptr + x * opp + dec) = ((unsigned char *)(&color2))[4 - opp + dec];
// 		}
// 	}
// }

// int main()
// {
// 	void *mlx;
// 	void *win;
// 	void *im;
// 	char *data;
// 	int	bpp;
// 	int sl;
// 	int endian;

// 	if (!(mlx = mlx_init()))
// 	{
// 		printf(" !! KO !!\n");
// 		exit(1);
// 	}
// 	printf(" => Window1 %dx%d \"Title 1\" ...\n",WIN_SX,WIN_SY);
// 	if (!(win = mlx_new_window(mlx,WIN_SX,WIN_HEIGHT,"Title1")))
// 	{
// 		printf(" !! KO !!\n");
// 		exit(1);
// 	}
// 	if (!(im = mlx_new_image(mlx, WIN_SX, WIN_HEIGHT)))
// 	{
// 		printf(" !! KO !!\n");
// 		exit(1);
// 	}
// 	mlx_key_hook(win,key_win,0);
// 	data = mlx_get_image_addr(im, &bpp, &sl, &endian);
//   	printf("OK (bpp1: %d, sizeline1: %d endian: %d)\n",bpp,sl,endian);
// 	color_map(mlx, data, bpp, sl, WIN_SX, WIN_HEIGHT, endian, 1);
// 	printf(" => Put Image ...\n");
// 	mlx_put_image_to_window(mlx, win, im, 0, 0);
// 	mlx_loop(mlx);
// 	// sleep(2);
// }
