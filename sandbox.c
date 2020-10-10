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

	t_cub	cub;
	// void *mlx_ptr = mlx_init();
	char *line;
	int fd = open("test.cub", O_RDONLY);
	get_next_line(fd, &line);
	// t_window window;
	// mlx_get_screen_size(mlx_ptr, &window.width, &window.height);
	// printf("width: %d, height: %d\n", window.width, window.height);

	// line = delete_leading_spaces(line);
	// printf("check format: %d\n", check_formatting_resolution(line));
	// if (check_formatting_resolution(line) == 0)
	// {
	// 	parse_resolution(line, &window);
	// 	printf("width: %d, height: %d\n", window.width, window.height);
	// }
	get_next_line(fd, &line);
	line = delete_leading_spaces(line);
	printf("check format: %d\n", check_formatting_texture(line));


}
