#include "header.h"


void *mlx;
void *mlx_win;
int current_imgnbr;
t_data img1;
t_data img2;
t_texture texture;
int grid[11][15] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

int key_win(int key, void *p)
{
	(void)p;
	// printf("Key in Win1 : %d\n", key);
	if (key == 0xFF1B)
		exit(0);
	else if (key == 119)
		player.dir_ver = 1;
	else if (key == 115)
		player.dir_ver = -1;
	else if (key == 97)
		player.dir_hor = -1;
	else if (key == 100)
		player.dir_hor = 1;
	else if (key == 65361)
		player.turn_dir = -1;
	else if (key == 65363)
		player.turn_dir = 1;
	return 1;
}

int key_release_win(int key, void *p)
{
	(void)p;
	printf("Key Release in Win1 : %d\n", key);
	if (key == 119)
		player.dir_ver = 0;
	else if (key == 115)
		player.dir_ver = 0;
	else if (key == 97)
		player.dir_hor = 0;
	else if (key == 100)
		player.dir_hor = 0;
	else if (key == 65361)
		player.turn_dir = 0;
	else if (key == 65363)
		player.turn_dir = 0;
	return 1;

}

int clear_img(t_data* img)
{
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		for (int j = 0; j < WIN_HEIGHT; j++)
		{
			my_mlx_pixel_put(img, i, j, 0X00000000);
		}
	}
	return 1;
}

int render_next_frame(void *p)
{
	(void)p;
	t_data img = (current_imgnbr == 0 ? img1 : img2);
	current_imgnbr = (current_imgnbr == 0 ? 1 : 0);
	// clear_img(&img);
	update_player();
	update_rays();
	// plot_line(&img
	// 			, player.x
	// 			, player.y
	// 			, player.x + cos(player.rotation_angle) * 20
	// 			, player.y + sin(player.rotation_angle) * 20);
	render3d(&img);
	render_player(&img);
	render_grid(&img);
	render_rays(&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_put_image_to_window(mlx, mlx_win, texture.img.img, 0, 0);
	return (1);
}


int destroy_win(void *p)
{
	(void)p;
	exit(0);
}

int main(void)
{

	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	img1.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img1.addr = mlx_get_data_addr(img1.img, &(img1.bits_per_pixel), &(img1.line_length),
								 &(img1.endian));
	img2.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img2.addr = mlx_get_data_addr(img2.img, &(img2.bits_per_pixel), &(img2.line_length),
								 &(img2.endian));
	texture.img.img = mlx_xpm_file_to_image(mlx, "textures/eagle.xpm", &texture.width, &texture.height);
	texture.img.addr = mlx_get_data_addr(texture.img.img, &(texture.img.bits_per_pixel), &(texture.img.line_length),
										 &(texture.img.endian));
	// render_grid(&img);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, 2, 1L << 0, key_win, 0);
	mlx_hook(mlx_win, 3, 1L << 1, key_release_win, 0);
	mlx_hook(mlx_win, 17, 1L << 17, destroy_win, 0);
	mlx_loop_hook(mlx, render_next_frame, 0);

	mlx_loop(mlx);
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
// 	data = mlx_get_data_addr(im, &bpp, &sl, &endian);
//   	printf("OK (bpp1: %d, sizeline1: %d endian: %d)\n",bpp,sl,endian);
// 	color_map(mlx, data, bpp, sl, WIN_SX, WIN_HEIGHT, endian, 1);
// 	printf(" => Put Image ...\n");
// 	mlx_put_image_to_window(mlx, win, im, 0, 0);
// 	mlx_loop(mlx);
// 	// sleep(2);
// }
