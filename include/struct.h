/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:15:24 by aclose            #+#    #+#             */
/*   Updated: 2020/11/10 01:38:14 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef int			t_bool;

typedef enum		e_error
{
	UNKNOWN_IDENTIFIER = 1,
	SAME_IDENTIFIER_TWICE,
	MALLOC_ERROR,
	SMALLER_THAN_MINIMUM_RESOLUTION,
	COLOR_PARSING,
	MISSING_ELEMENTS,
	CONFIG_FILE_READING,
	FORMATTING_TEXTURE,
	FORMATTING_RESOLUTION,
	FORMATTING_COLOR,
	UNKNOWN_CHAR_IN_MAP,
	TWO_PLAYERS_IN_MAP,
	PLAYER_NOT_FOUND_IN_MAP,
	MAP_IS_NOT_CLOSED,
	LOADING_TEXTURES,
	EMPTY_LINE_IN_THE_MIDDLE,
	MINILIBX_ERROR
}					t_error;

typedef union		u_color
{
	unsigned		hexcode;
	struct			s_color
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
	}				rgb;
}					t_color;

typedef struct		s_window
{
	void	*win_ptr;
	int		width;
	int		height;

}					t_window;

typedef struct		s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}					t_image;

typedef struct		s_texture
{
	char	*filepath;
	int		height;
	int		width;
	t_image	img;
}					t_texture;

typedef struct		s_texture_renderer
{
	unsigned	color;
	double		texture_y;
	double		texture_x;
	double		step_texture;
	double		ratio_of_texture_to_appear;
}					t_texture_renderer;

typedef struct		s_intersection_finder
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	next_touch_x;
	double	next_touch_y;
}					t_intersection_finder;

typedef struct		s_player
{
	double	x;
	double	y;
	int		dir_hor;
	int		dir_ver;
	int		turn_dir;
	double	rotation_angle;
	double	speed;
}					t_player;

typedef struct		s_ray
{
	double		angle;
	double		hor_wall_hit_x;
	double		hor_wall_hit_y;
	int			found_hor_wall_hit;
	double		ver_wall_hit_y;
	double		ver_wall_hit_x;
	int			found_ver_wall_hit;
	double		wall_hit_x;
	double		wall_hit_y;
	double		distance;
	int			is_vertical_hit;
	int			is_ray_facing_down;
	int			is_ray_facing_right;
	double		wall_strip_height;
	double		normalized_wall_strip_height;
	t_texture	*texture;
}					t_ray;

typedef	struct		s_rectangle
{
	int			x;
	int			y;
	int			width;
	int			height;
	unsigned	color;
}					t_rectangle;

typedef struct		s_sprite
{
	double	x;
	double	y;
	double	distance;
	double	angle;
	t_bool	is_visible;
	double	dx;
	double	dy;
	double	height;
	double	width;
	double	tex_x;
	double	tex_y;
	double	initial_x;
	double	initial_y;
}					t_sprite;

typedef struct		s_map
{
	char		**rows;
	int			*row_lengths;
	int			height;
	int			malloced_height;
	int			width;
	int			sprite_count;
	t_sprite	*sprites;
}					t_map;

typedef	struct		s_cub
{
	void		*mlx_ptr;
	int			fd_config_file;
	t_window	window;
	t_texture	textures[5];
	t_color		colors[2];
	unsigned	already_parsed;
	t_error		error_code;
	t_player	player;
	t_map		map;
	t_image		image;
	t_ray		*rays;
	int			number_of_rays;
	double		distance_projection_plane;
	int			tile_size;
	t_bool		should_save_first_frame;
}					t_cub;

typedef struct		s_parser
{
	char		*identifier;
	int			(*parsing_function)(char *, t_cub *);
	int			(*format_checking_function)(char *);
	unsigned	parsing_code;
}					t_parser;

typedef struct		s_direction
{
	int dx;
	int dy;
}					t_direction;

enum				e_textures
{
	NO,
	SO,
	WE,
	EA,
	S
};

enum				e_parsing_code
{
	NORTH_TEXTURE = 1,
	SOUTH_TEXTURE = 1 << 1,
	WEST_TEXTURE = 1 << 2,
	EAST_TEXTURE = 1 << 3,
	SPRITE_TEXTURE = 1 << 4,
	RESOLUTION = 1 << 5,
	FLOOR_COLOR = 1 << 6,
	CEILING_COLOR = 1 << 7
};

enum				e_colors
{
	FLOOR,
	CEILING
};

enum				e_cell
{
	SPACE = ' ',
	EMPTY = '0',
	WALL = '1',
	SPRITE = '2',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W'
};

#endif
