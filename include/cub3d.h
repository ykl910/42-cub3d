/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:57:05 by kyang             #+#    #+#             */
/*   Updated: 2025/04/17 17:07:09 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define E 101
# define SPACE 32
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364
# define MINIMAP_SCALE 5
# define WEAPONE_SCALE 10

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

typedef struct s_player	t_player;

typedef struct s_map
{
	int		x;
	int		y;
	int		size;
	int		h_max;
	int		w_max;
	int		map_start;
	int		started_map;
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

typedef struct s_weapon
{
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*img;
	int		*data;
	double	pos_x;
	double	pos_y;

}	t_weapon;

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
	char		*texture_path[8];
	int			ceiling_color;
	int			floor_color;
	int			bonus;
	int			c;
	int			door_opened;
	int			player_count;
	t_player	*player;
	t_map		*map;
	t_texture	*textures[6];
	t_weapon	*weapon[4];
	int			shooting_frame;
	int			is_shooting;
	int			shooting_timer;
	int			parsed_texture;
}	t_env;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		map_x;
	int		map_y;
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	near_dist_x;
	double	near_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}	t_player;

// init
void	init_env(t_env *env);
void	init_texture(t_env *env);
void	init_map(t_map *map, t_env *env, char *file_map);

// parsing
void	parse_texture(char *line, t_env *env);
int		color_convert(char *color, t_env *env);
void	map_delimit(t_map *map, char *file_map, t_env *env);
void	map_parsing(t_env *env, char *file_map);
void	check_map_closed_and_connected(t_env *env);
void	check_cub(char *file_map, t_env *env);
void	check_extra_content_after_map(int fd, t_env *env);

// raycasting
void	init_player_dir(t_player *player, t_map *map);
void	calculate_distance(t_player *player);
void	dda(t_player *player);
void	add_door_side(t_player *player, t_map *map);
void	calculate_tex_x(t_player *player, t_env *env);
int		calculate_line(t_player *player, t_env *env);

void	draw_line(t_player *player, t_env *env, int x, int y);
void	draw_ceiling_floor(t_env *env, t_player *player, int x);
void	raycasting(t_player *player, t_map *map, t_env *env);

void	init_mlx(t_env	*env);
void	draw_pixel_to_image(t_env *env, int x, int y, int color);

// minimap
void	draw_minimap(t_env *env);
void	draw_player_on_minimap(t_env *env);
void	draw_square(t_env *env, int x, int y, int color);
void	draw_player_dir_on_minimap(t_env *env);

// door
void	open_door(t_env *env);
void	close_door(t_env *env);

// weapon
void	weapon_init(t_env *env);
void	draw_weapon(t_env *env);

// mlx events
int		render_loop(t_env *env);
int		key_press(int keycode, t_env *env);
int		key_release(int keycode, t_env *env);
int		mouse_move(int x, int y, t_env *env);
void	player_move_backward(t_player *player, t_map *map);
void	player_move_forward(t_player *player, t_map *map);
void	player_move_left(t_player *player, t_map *map);
void	player_move_right(t_player *player, t_map *map);
void	player_rotate_right(t_player *player);
void	player_rotate_left(t_player *player);

// utils
void	free_ressources(t_env *env);
int		handle_destroy(t_env *env);
void	free_char_arr(char **list);
void	print_map(t_map *map);
int		ft_invalid(char *error_message, t_env *env, char *line);
char	*ft_calloc_two(int count, size_t size);

#endif
