


#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920

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

typedef struct s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	int			x;
	int			y;
	int			zoom;
	t_player	*player;
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
	int			color;
} t_player;

// parsing
void	map_init(t_map *map);
void	map_delimit(t_map *map, char *file_map);
int		ft_invalid(char *error_message);
void	map_parsing(t_map *map, char *file_map);

void	init_player_dir(t_player *player, t_map *map);
void	init_player_cam(t_player *player, t_map *map, t_env *env);

void	init_mlx(t_env	*env, t_map *map, t_player *player);
void	draw_pixel_to_image(t_env *env, int x, int y, int color);


#endif
