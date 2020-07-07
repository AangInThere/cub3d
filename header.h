#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>

#define TILE_SIZE 80
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define	WIN_WIDTH	(MAP_NUM_COLS * TILE_SIZE)
#define	WIN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
#define XSPEED (TILE_SIZE / 25)
#define YSPEED XSPEED
#define PLAYER_SIZE 5
#define M_PI 3.14159265358979323846
#define ROTATION_SPEED (4 * (M_PI / 180))
#define FOV_ANGLE (M_PI / 3)
#define WALL_STRIP_WIDTH  1
#define NUM_RAYS  (WIN_WIDTH / WALL_STRIP_WIDTH)
#define MINIMAP_SCALE_FACTOR 0.2
// #define NUM_RAYS  1

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_texture
{
	t_data	img;
	int		width;
	int		height;
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

extern t_player	player;
extern int		grid[11][15];
extern t_ray	rays[NUM_RAYS];
extern t_texture texture;

int put_square_at(t_data *data, int x, int y, int size, int color);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int put_rectangle_at(t_data *data, int x, int y, int width, int height, int color);

int WallAt(int x, int y);

int update_player();
int render_player(t_data *img);
int reset_player(int keycode, void *param);

void plot_line(t_data *data, int x0, int y0, int x1, int y1);
void render_grid(t_data *data);

void update_rays(void);
void render_rays(t_data *img);
double normalize_angle(double angle);
void find_horizontal_intersection(t_ray *ray);
void find_vertical_intersection(t_ray *ray);
double distanceBetween(double x0, double y0, double x1, double y1);
void select_shortest_wall_hit(t_ray *ray);
void render3d(t_data *img);
double normalize_wall_height(double height);
int find_texture_x(t_ray ray);
void render_ray(t_data *img, t_ray ray, int ray_x);
