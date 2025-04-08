


#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define BLUE  0x0000FF
# define GREEN 0x00FF00
# define ESC 65307
# define A 97
# define D 100
# define S 115
# define W 119
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_player t_player;

typedef struct s_map
{
	int		x;
	int		y;
	int		size;
	int		h_max;
	int		w_max;
	int		map_start;
	char	**final_map;

}	t_map;

typedef struct s_texture
{
	int		width;
	int		height;
	int		*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*img;
}	t_texture;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			keys[70000];
	char		*texture_path[6];
	int			ceiling_color;
	int			floor_color;
	t_player	*player;
	t_map		*map;
	t_texture	*textures[4];
}	t_env;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	int		mapX;
	int		mapY;
	double	camX;
	double	rayDirX;
	double	rayDirY;
	double	nearDistX;
	double	nearDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	double	wallX;
	int		texX;
	int		texY;
} t_player;


// init
void	keys_init(t_env *env);
void	init_texture(t_env *env);


//	map parsing thomas
void	*ft_calloc_two(size_t count, size_t size);
void	ft_btwo(void *s, size_t n);
void	print_map(t_map *map);
void	check_map_wall(char *line, t_env *env);


// parsing
void	parse_texture(char *line, t_env *env);

void	map_init(t_map *map, t_env *env);	
void	map_delimit(t_map *map, char *file_map, t_env *env);
int		ft_invalid(char *error_message, t_env *env);
void	map_parsing(t_env *env, char *file_map);

void	init_player_dir(t_player *player, t_map *map);
void	init_player_cam(t_player *player, t_map *map, t_env *env);

void	init_mlx(t_env	*env);
void	draw_pixel_to_image(t_env *env, int x, int y, int color);
int		render_loop(t_env *env);
int		key_press(int keycode, t_env *env);
int		key_release(int keycode, t_env *env);
int		mouse_move(int x, int y, t_env *env);


// keys
void	player_move_backward(t_player *player, t_map *map);
void	player_move_forward(t_player *player, t_map *map);
void	player_move_left(t_player *player, t_map *map);
void	player_move_right(t_player *player, t_map *map);

void	player_rotate_right(t_player *player);
void	player_rotate_left(t_player *player);

void	free_ressources(t_env *env);
int		handle_destroy(t_env *env);
void	free_char_arr(char **list);


int color_convert(char *color);
#endif
