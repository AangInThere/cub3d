#ifndef HEADER_H
# define HEADER_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

# define TILE_SIZE 80
# define MAP_NUM_ROWS 11
# define MAP_NUM_COLS 15
# define	WIN_WIDTH	(MAP_NUM_COLS * TILE_SIZE)
# define	WIN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
# define XSPEED ((double)TILE_SIZE / 20.0)
# define YSPEED XSPEED
# define PLAYER_SIZE 5
# define M_PI 3.14159265358979323846
# define ROTATION_SPEED (4 * (M_PI / 180) / 3.0)
# define FOV_ANGLE (M_PI / 3)
# define WALL_STRIP_WIDTH  1
# define NUM_RAYS  (WIN_WIDTH / WALL_STRIP_WIDTH)
// # define NUM_RAYS  1
# define MINIMAP_SCALE_FACTOR 0.2
# define TRUE 1
# define FALSE 0
# define MINIMUM_WIDTH 200
# define MINIMUM_HEIGHT 200

typedef int t_bool;

typedef union
{
	unsigned int hexcode;
	struct
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
	} rgb;
} t_color;

typedef struct s_window
{
	void	*win_ptr;
	int		width;
	int		height;

} t_window;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_mlx;

typedef struct s_image
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_image;

typedef struct s_texture
{
	char	*filepath;
	int		height;
	int		width;
	t_image	img;
} t_texture;


typedef struct s_player
{
	double	x;
	double	y;
	int dir_hor;
	int dir_ver;
	int turn_dir;
	double rotation_angle;
}				t_player;

typedef struct	s_ray
{
	double	angle;
	double	hor_wall_hit_x;
	double	hor_wall_hit_y;
	int		found_hor_wall_hit;
	double	ver_wall_hit_y;
	double	ver_wall_hit_x;
	int		found_ver_wall_hit;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		is_vertical_hit;
	int		is_ray_facing_down;
	int		is_ray_facing_right;
}				t_ray;

typedef	struct s_cub
{
	void		*mlx_ptr;
	t_window	window;
	t_texture	textures[5];
	t_color		colors[2];
	unsigned	already_parsed;
	unsigned	error_code;
}				t_cub;

typedef struct s_parser
{
	char *identifier;
	int (*parsing_function)(char *, t_cub *);
	int (*format_checking_function)(char *);
	unsigned parsing_code;
} t_parser;

enum e_textures
{
	NO,
	SO,
	WE,
	EA,
	S
};

enum e_parsing_code
{
	NORTH_TEXTURE = 1,
	SOUTH_TEXTURE = 1 << 2,
	WEST_TEXTURE = 1 << 3,
	EAST_TEXTURE = 1 << 4,
	SPRITE_TEXTURE = 1 << 5,
	RESOLUTION = 1 << 6,
	FLOOR_COLOR = 1 << 7,
	CEILING_COLOR = 1 << 7
};

enum e_colors
{
	FLOOR,
	CEILING
};

extern t_player	player;
extern int		grid[11][15];
extern t_ray	rays[NUM_RAYS];
extern t_texture texture;

int put_square_at(t_image *data, int x, int y, int size, int color);
void my_mlx_pixel_put(t_image *data, int x, int y, int color);
int put_rectangle_at(t_image *data, int x, int y, int width, int height, int color);

int WallAt(int x, int y);

int update_player();
int render_player(t_image *img);
int reset_player(int keycode, void *param);

void plot_line(t_image *data, int x0, int y0, int x1, int y1);
void render_grid(t_image *data);

void update_rays(void);
void render_rays(t_image *img);
double normalize_angle(double angle);
void find_horizontal_intersection(t_ray *ray);
void find_vertical_intersection(t_ray *ray);
double distanceBetween(double x0, double y0, double x1, double y1);
void select_shortest_wall_hit(t_ray *ray);
void render3d(t_image *img);
double normalize_wall_height(double height);
int find_texture_x(t_ray ray);
void render_ray(t_image *img, t_ray ray, int ray_x);

int check_formatting_resolution(char *line);
int parse_resolution(char *line, t_cub *cub);


char *delete_leading_spaces(char *line);
t_bool	is_empty_line(char *line);
void skip_spaces(char **line);
void skip_digits(char **line);
int check_file_name(char *filename);

int check_formatting_texture(char *line);
int parse_texture(char *line, t_cub *cub);


int	parse_color(char *line, t_cub *cub);
int	parse_color_numbers(char *line, t_color *color);
int	check_formatting_color(char *line);
int check_formatting_color_number(char **line);
void skip_until_next_number(char **line);

int parse_one_line(char *line, t_cub *cub);
int parse_premap(int fd, t_cub *cub);

#endif
