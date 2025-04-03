/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:28:09 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/03 11:41:26 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_init(t_map *map)
{
	map->x = 0;
	map->y = 0;
	map->h_max = 0;
	map->w_max = 0;
	map->map_start = 0;
	map->final_map = NULL;
}

void	map_delimit(t_map *map, char *file_map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file_map, O_RDONLY);
	if (fd < 0)
		ft_invalid("map invalid - no permission\n");
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		if (line[0] == ' ' || line[0] == '1')
		{
			while(line[i])
				i++;
			if (map->w_max < i)
				map->w_max = i;
			map->h_max++;
		}
		else
			map->map_start++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	map_parsing(t_map *map, char *file_map)
{
	int		fd;
	char	*line;

	fd = open(file_map, O_RDONLY);
	map->final_map = ft_calloc(map->h_max, sizeof(int *));
	if (!map->final_map)
		ft_invalid("Malloc failled !\n");
	while (map->map_start-- > 0)
	{
		line = get_next_line(fd);
		free(line);
	}
	while (map->y < map->h_max)
	{
		map->final_map[map->y] = ft_calloc(map->w_max, sizeof(int));
		if (!map->final_map[map->y])
			ft_invalid("Malloc failled !\n");
		line = get_next_line(fd);
		map->x = -1;
		while (line[++map->x] != '\n')
			map->final_map[map->y][map->x] = (line[map->x]);
		map->y++;
		free(line);
	}
	close(fd);
}

void	init_player_dir(t_player *player, t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->h_max)
	{
		x = 0;
		while (x < map->w_max)
		{
			if (map->final_map[y][x] == 'N' || map->final_map[y][x] == 'S' || map->final_map[y][x] == 'E' || map->final_map[y][x] == 'W')
			{
				player->posX = x;
				player->posY = y;
				if (map->final_map[y][x] == 'N')
				{
					player->dirX = -1;
					player->dirY = 0;
					player->planeX = 0;
					player->planeY = 0.66;
				}
				else if (map->final_map[y][x] == 'S')
				{
					player->dirX = 1;
					player->dirY = 0;
					player->planeX = 0;
					player->planeY = -0.66;
				}
				else if (map->final_map[y][x] == 'E')
				{
					player->dirX = 0;
					player->dirY = 1;
					player->planeX = 0.66;
					player->planeY = 0;

				}
				else if (map->final_map[y][x] == 'W')
				{
					player->dirX = 0;
					player->dirY = -1;
					player->planeX = -0.66;
					player->planeY = 0;
				}
				map->final_map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

void	init_player_cam(t_player *player, t_map *map, t_env *env)
{
	int		x;
	int		y;

	y = 0;
	x = 0;
	player->hit = 0;
	while (x < WINDOW_WIDTH)
    {
		player->camX = 2 * x / (double)WINDOW_WIDTH - 1;
		player->rayDirX = player->dirX + player->planeX * player->camX;
		player->rayDirY = player->dirY + player->planeY * player->camX;

		player->mapX = (int)player->posX;
		player->mapY = (int)player->posY;

		player->deltaDistX = sqrt(1 + (player->rayDirY * player->rayDirY) / (player->rayDirX * player->rayDirX));
		player->deltaDistY = sqrt(1 + (player->rayDirX * player->rayDirX) / (player->rayDirY * player->rayDirY));

		if (player->rayDirX < 0)
		{
			player->stepX = -1;
			player->nearDistX = (player->posX - player->mapX) * player->deltaDistX;
		}
		else
		{
			player->stepX = 1;
			player->nearDistX = (player->mapX + 1.0 - player->posX) * player->deltaDistX;
		}
		if (player->rayDirY < 0)
		{
			player->stepY = -1;
			player->nearDistY = (player->posY - player->mapY) * player->deltaDistY;
		}
		else
		{
			player->stepY = 1;
			player->nearDistY = (player->mapY + 1.0 - player->posY) * player->deltaDistY;
		}
		//perform DDA
		printf("player->hit = %d\n", player->hit);
		while (player->hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (player->nearDistX < player->nearDistY)
			{
			  player->nearDistX += player->deltaDistX;
			  player->mapX += player->stepX;
			  if (player->stepX == 1)
				player->side = 0;
			  else
			  	player->side = 1;
			}
			else
			{
			  player->nearDistY += player->deltaDistY;
			  player->mapY += player->stepY;
			  if (player->stepY == 1)
				player->side = 2;
			  else
			  	player->side = 3;
			}
			//Check if ray has hit a wall
			if (map->final_map[player->mapX][player->mapY] == '1')
				player->hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)

		if(player->side == 0 || player->side == 1)
			player->perpWallDist = (player->nearDistX - player->deltaDistX);
		else
			player->perpWallDist = (player->nearDistY - player->deltaDistY);

		//Calculate height of line to draw on screen
		player->lineHeight = (int)(WINDOW_HEIGHT / player->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		player->drawStart = -player->lineHeight / 2 + WINDOW_HEIGHT / 2;
		if(player->drawStart < 0)
			player->drawStart = 0;
		player->drawEnd = player->lineHeight / 2 + WINDOW_HEIGHT / 2;
		if(player->drawEnd >= WINDOW_HEIGHT)
			player->drawEnd = WINDOW_HEIGHT - 1;
		if (player->side == 0)		// Face Est
			player->color = 0xFF0000;	// Rouge
		else if (player->side == 1)	// Face Ouest
			player->color = 0x990000;	// Rouge plus sombre
		else if (player->side == 2) // Face Sud
			player->color = 0x00FF00;	// Vert
		else 			// Face Nord
			player->color = 0x009900;	// Vert plus sombre
		// printf("player->drawStart = %d\n", player->drawStart);
		y = player->drawStart;
		// printf("y = %d\n", y);
		// printf("player->drawEnd = %d\n", player->drawEnd);
		while (y <= player->drawEnd)
		{
			draw_pixel_to_image(env, x, y, player->color);
			y++;

		}
		x++;
		//printf("x = %d\n", x);
	}
}

void	draw_pixel_to_image(t_env *env, int x, int y, int color)
{
	int	pixel_index;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		pixel_index = (y * env->line_length) + (x * (env->bits_per_pixel / 8));
		*(int *)(env->addr + pixel_index) = color;
	}
}

void	init_mlx(t_env	*env, t_map *map, t_player *player)
{
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		return ;
	env->win = mlx_new_window(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (env->win == NULL)
		return ;
	env->img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, \
	&env->line_length, &env->endian);
	if (env->addr == NULL)
		return ;
	init_player_cam(player, map, env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_loop(env->mlx);
}
