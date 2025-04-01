


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

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
	int		zoom;
}	t_image;

// typedef struct s_map
// {
// 	int		x;
// 	int		y;
// 	int		xi;
// 	int		yi;
// 	int		size;
// }	t_map;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_image 	img;
	t_player	*player;
}	t_mlx;

typedef struct s_player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double camX;
	double rayDirX;
	double rayDirY;
	double nearDistX;
	double nearDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
} t_player;

#endif
