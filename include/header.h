/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:11:18 by aclose            #+#    #+#             */
/*   Updated: 2020/11/11 13:58:01 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# ifndef __USE_XOPEN
#  define __USE_XOPEN
# endif
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"
# include "struct.h"
# define TILE_SIZE 80
# define PLAYER_SIZE 5
# define PI_90 0.03490658503
# define ROTATION_SPEED PI_90
# define PI_3 1.0471975512
# define FOV_ANGLE PI_3
# define WALL_STRIP_WIDTH  1
# define MINIMAP_SCALE_FACTOR 0.2
# define TRUE 1
# define FALSE 0
# define MINIMUM_WIDTH 20
# define MINIMUM_HEIGHT 20

void		my_mlx_pixel_put(t_image *data, int x, int y, int color);
int			put_rectangle(t_image *data, t_rectangle rectangle);

int			setup_cub3d(t_cub *cub);
int			setup_window_and_image(t_cub *cub);
int			setup_hooks(t_cub *cub);
int			set_player_starting_position(t_player *player
				, t_map map, t_cub *cub);
int			setup_sprites(t_cub *cub);
int			ft_count_sprites(t_map *map);

int			update_player(t_cub *cub);
int			is_wall_at(int x, int y, t_map map, t_cub *cub);
int			is_sprite_at(int x, int y, t_map map, t_cub *cub);

void		render_minimap(t_image *data, t_cub *cub);
void		render_player_on_minimap(t_image *img, t_cub *cub, int square_size);
int			put_square(t_image *data, int x, int y, int size);
void		plot_circle(t_image *img, int xm, int ym, int r);

void		update_rays(t_cub *cub);
void		find_horizontal_intersection(t_ray *ray, t_cub *cub);
void		find_vertical_intersection(t_ray *ray, t_cub *cub);
void		vert_intersec_setup(t_ray *ray, t_cub *cub
				, t_intersection_finder *s);
void		hor_intersec_setup(t_ray *ray, t_cub *cub
				, t_intersection_finder *s);

double		normalize_angle(double angle);
double		distance_between(double x0, double y0, double x1, double y1);
void		select_shortest_wall_hit(t_ray *ray, t_cub *cub);
double		normalize_wall_height(double height, t_cub *cub);
double		find_texture_x(t_ray ray, t_cub *cub);

int			render_next_frame(t_cub *cub);
void		render_walls_floor_and_ceiling(t_image *img, t_cub *cub);
void		render_wall_strip(t_image *img, t_ray ray, int ray_x, t_cub *cub);
t_texture	*find_correct_texture(t_ray ray, t_cub *cub);
void		render_floor_and_ceiling(t_image *img, t_cub *cub, int ray_x);

int			check_formatting_resolution(char *line);
int			parse_resolution(char *line, t_cub *cub);

char		*delete_leading_spaces(char *line);
t_bool		is_empty_line(char *line);
void		skip_spaces(char **line);
void		skip_digits(char **line);
int			check_file_name(char *filename);

int			check_formatting_texture(char *line);
int			parse_texture(char *line, t_cub *cub);
int			load_textures(t_cub *cub);

int			parse_color(char *line, t_cub *cub);
int			parse_color_numbers(char *line, t_color *color);
int			check_formatting_color(char *line);
int			check_formatting_color_number(char **line);
void		skip_until_next_number(char **line);

int			parse_one_line(char *line, t_cub *cub);
int			parse_premap(int fd, t_cub *cub);
int			each_element_of_premap_is_parsed(unsigned already_parsed);

int			parse_map(int fd, t_cub *cub);
int			get_map_from_file(int fd, t_map *map);
char		**realloc_map(t_map *map);
int			remove_empty_lines_at_the_end(t_map *map);
int			populate_row_lengths(t_map *map);

int			check_map(t_map *map);
int			check_characters_and_player_in_map(t_map *map);
t_bool		is_an_edge(t_map *map, int x, int y);
t_bool		is_inside_map(t_map *map, int x, int y);
int			check_if_map_is_not_in_2_parts(t_map *map);

int			parse(t_cub *cub, char *filename);

void		print_error(char *error_msg);
int			free_and_destroy(t_cub *cub);
int			print_error_and_clean_exit(char *error_msg, t_cub *cub);
int			free_and_destroy_textures(t_cub *cub);

int			key_win(int key, t_cub *cub);
int			key_release_win(int key, t_cub *cub);
int			destroy_win(t_cub *cub);

void		update_sprite(t_sprite *sprite, t_player player, t_cub *cub);
void		render_sprite(t_image *img, t_cub *cub, t_sprite *sprite);
int			sort_sprites(t_map *map);
int			update_sprites(t_cub *cub);
int			render_sprites(t_image *img, t_cub *cub);
unsigned	get_color_from_texture(t_texture *texture, t_sprite *sprite
					, double current_y, double current_x);

int			save_bmp_and_exit(t_cub *cub);
int			write_bmp_header(t_cub *cub, int fd, int filesize);
int			write_bmp_pixel(t_cub *cub, int fd, int pad, t_image *image);

#endif
