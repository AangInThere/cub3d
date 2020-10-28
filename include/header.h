#ifndef HEADER_H
# define HEADER_H
# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# define __USE_XOPEN
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
// # define M_PI 3.14159265358979323846
# define ROTATION_SPEED (4.0 * (M_PI / 180.0) / 3.0)
# define FOV_ANGLE (M_PI / 3)
# define WALL_STRIP_WIDTH  1
# define NUM_RAYS  (WIN_WIDTH / WALL_STRIP_WIDTH)
// # define NUM_RAYS  1
// # define MINIMAP_SCALE_FACTOR 0.2
# define MINIMAP_SCALE_FACTOR 0.2
# define TRUE 1
# define FALSE 0
# define MINIMUM_WIDTH 20
# define MINIMUM_HEIGHT 20

typedef int t_bool;

typedef union
{
	unsigned int hexcode;
	struct
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
	} rgb;
} t_color;

typedef struct s_window
{
	void	*win_ptr;
	int		width;
	int		height;

} t_window;

typedef struct s_image
{
	void *img_ptr;
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
	t_texture	*texture;
}				t_ray;

typedef struct s_sprite
{
	double x;
	double y;
	double distance_from_player;
	double angle;
	t_bool is_visible;
}	t_sprite;

typedef struct s_map
{
	char **rows;
	int	height;
	int malloced_height;
	int width;
	int	sprite_count;
	t_sprite	*sprites;
}	t_map;

typedef	struct s_cub
{
	void		*mlx_ptr;
	t_window	window;
	t_texture	textures[5];
	t_color		colors[2];
	unsigned	already_parsed;
	unsigned	error_code;
	t_player	player;
	t_map		map;
	t_image		images[2];
	int			current_image;
	t_ray		*rays;
	int			number_of_rays;
	int			tile_size;
	int			tile_width;
	int			tile_height;
	t_sprite	sprite;
}				t_cub;

typedef struct s_parser
{
	char *identifier;
	int (*parsing_function)(char *, t_cub *);
	int (*format_checking_function)(char *);
	unsigned parsing_code;
} t_parser;

typedef struct s_direction
{
	int dx;
	int dy;
}	t_direction;

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
	SOUTH_TEXTURE = 1 << 1,
	WEST_TEXTURE = 1 << 2,
	EAST_TEXTURE = 1 << 3,
	SPRITE_TEXTURE = 1 << 4,
	RESOLUTION = 1 << 5,
	FLOOR_COLOR = 1 << 6,
	CEILING_COLOR = 1 << 7
};

enum e_colors
{
	FLOOR,
	CEILING
};

enum e_cell
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

// extern t_player	player;
// extern int		grid[11][15];
// extern t_ray	ray_array[NUM_RAYS];
// extern t_texture texture;

int put_square_at(t_image *data, int x, int y, int size, int color);
void my_mlx_pixel_put(t_image *data, int x, int y, int color);
int put_rectangle_at(t_image *data, int x, int y, int width, int height, int color);
void plot_line(t_image *data, int x0, int y0, int x1, int y1);
void plot_circle(t_image *img, int xm, int ym, int r, unsigned color);

int set_up_window_and_images_for_cub(t_cub *cub);
int set_player_starting_position(t_player *player, t_map map, t_cub *cub);
int ft_compute_tile_size(t_cub *cub);
int setup_sprites(t_cub *cub);
int	ft_count_sprites(t_map *map);

int update_player(t_cub *cub);
int WallAt(int x, int y, t_map map, t_cub *cub);

void render_grid(t_image *data, t_cub *cub);
int render_player(t_image *img, t_cub *cub);
void render_rays(t_image *img, t_cub *cub);
int clear_img(t_image *img, t_cub *cub);

void update_rays(t_cub *cub);
void find_horizontal_intersection(t_ray *ray, t_cub *cub);
void find_vertical_intersection(t_ray *ray, t_cub *cub);


double normalize_angle(double angle);
double distanceBetween(double x0, double y0, double x1, double y1);
void select_shortest_wall_hit(t_ray *ray, t_cub *cub);
double normalize_wall_height(double height, t_cub *cub);
int find_texture_x(t_ray ray, t_cub *cub);

int render_next_frame(t_cub *cub);
void render3d(t_image *img, t_cub *cub);
void render_ray(t_image *img, t_ray ray, int ray_x, t_cub *cub);
t_texture *find_correct_texture(t_ray ray, t_cub *cub);

int check_formatting_resolution(char *line);
int parse_resolution(char *line, t_cub *cub);

char *delete_leading_spaces(char *line);
t_bool	is_empty_line(char *line);
void skip_spaces(char **line);
void skip_digits(char **line);
int check_file_name(char *filename);

int check_formatting_texture(char *line);
int parse_texture(char *line, t_cub *cub);
int load_textures(t_cub *cub);

int parse_color(char *line, t_cub *cub);
int	parse_color_numbers(char *line, t_color *color);
int	check_formatting_color(char *line);
int check_formatting_color_number(char **line);
void skip_until_next_number(char **line);

int parse_one_line(char *line, t_cub *cub);
int parse_premap(int fd, t_cub *cub);
int each_element_of_premap_is_parsed(unsigned already_parsed);

int parse_map(int fd, t_cub *cub);
int get_map_from_file(int fd, t_map *map);
char **realloc_map(t_map *map);
int ft_compute_real_height(t_map *map);

int check_map(t_map *map);
int check_characters_and_player_in_map(t_map *map);
t_bool	is_an_edge(t_map *map, int x, int y);
t_bool is_inside_map(t_map *map, int x, int y);

int parse(t_cub *cub, char *filename);
void	print_error(char *error_msg);

int key_win(int key, t_cub *cub);
int key_release_win(int key, t_cub *cub);
int destroy_win(t_cub *cub);

// int update_sprite(t_cub *cub);
// int render_sprite(t_image *img, t_cub *cub);

int update_sprite(t_sprite *sprite, t_player player);
int render_sprite(t_image *img, t_cub *cub, t_sprite *sprite);
int sort_sprites(t_map *map);
int update_sprites(t_cub *cub);
int render_sprites(t_image *img, t_cub *cub);

#endif
