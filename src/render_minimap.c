#include "header.h"

void render_grid(t_image *data, t_cub *cub)
{
	int j;
	// int tile_width = cub->window.width / cub->map.width;
	// int tile_height = cub->window.height / cub->map.height;

	for (int i = 0; i < cub->map.height; i++)
	{
		for (j = 0; j < (int)ft_strlen(cub->map.rows[i]); j++)
		{
			if (cub->map.rows[i][j] == WALL || cub->map.rows[i][j] == SPACE)
			{
				put_square_at(data, MINIMAP_SCALE_FACTOR * j * cub->tile_size, MINIMAP_SCALE_FACTOR * i * cub->tile_size, MINIMAP_SCALE_FACTOR * cub->tile_size, 0x0032CD32);
				// put_square_at(data, MINIMAP_SCALE_FACTOR * j * TILE_SIZE, MINIMAP_SCALE_FACTOR * i * TILE_SIZE, MINIMAP_SCALE_FACTOR * TILE_SIZE, 0x0032CD32);
				// put_rectangle_at(data, MINIMAP_SCALE_FACTOR * j * cub->tile_size, MINIMAP_SCALE_FACTOR * i * cub->tile_size, cub->tile_size * MINIMAP_SCALE_FACTOR, cub->tile_size * MINIMAP_SCALE_FACTOR, 0x0032CD32);
			}
		}
		while (j < cub->map.width)
		{
			put_square_at(data, MINIMAP_SCALE_FACTOR * j * cub->tile_size, MINIMAP_SCALE_FACTOR * i * cub->tile_size, MINIMAP_SCALE_FACTOR * cub->tile_size, 0x0032CD32);
			// put_rectangle_at(data, MINIMAP_SCALE_FACTOR * j * cub->tile_size, MINIMAP_SCALE_FACTOR * i * cub->tile_size, cub->tile_size* MINIMAP_SCALE_FACTOR, cub->tile_size* MINIMAP_SCALE_FACTOR, 0x0032CD32);
			j++;
		}
	}
}

int render_player(t_image *img, t_cub *cub)
{
	// put_square_at(img, player.x - PLAYER_SIZE / 2, player.y - PLAYER_SIZE / 2, PLAYER_SIZE, 0X00FF0000);
	plot_circle(img, MINIMAP_SCALE_FACTOR * cub->player.x, MINIMAP_SCALE_FACTOR * cub->player.y, PLAYER_SIZE, 0X00FF0000);
	return 1;
}

void render_rays(t_image *img, t_cub *cub)
{
	for (int i = 0; i < cub->number_of_rays; i++)
	{
		plot_line(img,
				  MINIMAP_SCALE_FACTOR * cub->player.x,
				  MINIMAP_SCALE_FACTOR * cub->player.y,
				  MINIMAP_SCALE_FACTOR * cub->rays[i].wall_hit_x,
				  MINIMAP_SCALE_FACTOR * cub->rays[i].wall_hit_y);
	}
	// for (int i = 0; i < NUM_RAYS; i++)
	// {
	// 	plot_line(img,
	// 				cub->player.x,
	// 				cub->player.y,
	// 				cub->player.x + cos(ray_array[i].angle) * 20,
	// 				cub->player.y + sin(ray_array[i].angle) * 20);
	// }
}

int clear_img(t_image *img, t_cub *cub)
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
