#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "header.h"

int key_win(int key, void *p)
{
	(void)p;
	// printf("Key in Win1 : %d\n", key);
	if (key == 0xFF1B)
		exit(0);
	return (0);
}

int main()
{
	// int fd = open("fsdaf.txt", O_RDONLY);
	// if (fd == -1)
	// {
	// 	printf("af %s\n", strerror(errno));
	// 	perror("open");
	// }
	// void *mlx_ptr = mlx_init();
	// int screen_width;
	// int screen_height;
	// mlx_get_screen_size(mlx_ptr, &screen_width, &screen_height);
	// printf("width: %d, height: %d\n", screen_width, screen_height);
	// void *win_ptr = mlx_new_window(mlx_ptr, screen_width, screen_height, "test get screen size");
	// mlx_key_hook(win_ptr, key_win, NULL);
	// for (int i = screen_height - 70; i < screen_height; i++)
	// {
	// 	for (int j = 0; j < screen_width; j++)
	// 		mlx_pixel_put(mlx_ptr, win_ptr, j, i, 0xFF1B);
	// }
	// mlx_loop(mlx_ptr);

	// t_color color;
	// color.hexcode = 0X00FF00;
	// printf("%hhu, %hhu, %hhu; %u\n", color.rgb.r, color.rgb.g, color.rgb.b, color.hexcode);
	// color.rgb.b = 200;
	// printf("%hhu, %hhu, %hhu; %u\n", color.rgb.r, color.rgb.g, color.rgb.b, color.hexcode);

	t_cub	cub;
	ft_bzero(&cub, sizeof(cub));
	cub.mlx_ptr = mlx_init();
	// char *line;
	int fd = open("test.cub", O_RDONLY);
	// get_next_line(fd, &line);
	mlx_get_screen_size(cub.mlx_ptr, &cub.window.width, &cub.window.height);
	printf("width: %d, height: %d\n", cub.window.width, cub.window.height);

	// line = delete_leading_spaces(line);
	// printf("check format: %d\n", check_formatting_resolution(line));
	// if (check_formatting_resolution(line) == 0)
	// {
	// 	parse_resolution(line, &cub);
	// 	printf("width: %d, height: %d\n", cub.window.width, cub.window.height);
	// }
	// get_next_line(fd, &line);
	// line = delete_leading_spaces(line);
	// printf("check format: %d\n", check_formatting_texture(line));
	// if (check_formatting_texture(line) == 0)
	// {
	// 	parse_texture(line, &cub);
	// 	printf("filepath: %s|\n", cub.textures[S].filepath);
	// }
	// get_next_line(fd, &line);
	// line = delete_leading_spaces(line);
	// printf("check color format: %d\n", check_formatting_color(line));
	// if (check_formatting_color(line) == 0)
	// {
	// 	parse_color(line, &cub);
	// 	t_color color = cub.colors[CEILING];
	// 	printf("%hhu, %hhu, %hhu; %u\n", color.rgb.r, color.rgb.g, color.rgb.b, color.hexcode);
	// }
	printf("return of parse premap: %d\n", parse_premap(fd, &cub));
	get_map_from_file(fd, &(cub.map));
	printf("malloced: %d, actual: %d\n", cub.map.malloced_height, cub.map.height);
	check_map(&cub.map);
	for (int i = 0; i < cub.map.height; i++)
		printf("%s\n", cub.map.rows[i]);
	printf("check map: %d\n", check_characters_and_player_in_map(&cub.map));
}
