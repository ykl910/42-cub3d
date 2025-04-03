/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:28:09 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/03 13:24:27 by tbellest         ###   ########.fr       */
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
	map->final_map = ft_calloc(map->h_max, sizeof(char *));
	if (!map->final_map)
		ft_invalid("Malloc failled !\n");
	while (map->map_start-- > 0)
	{
		line = get_next_line(fd);
		free(line);
	}
	while (map->y < map->h_max)
	{
		map->final_map[map->y] = ft_calloc(map->w_max, sizeof(char));
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
	mlx_key_hook(env->win, handle_keypress, env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_loop(env->mlx);
}

int	handle_keypress(int keycode, t_env *env)
{
	if (keycode == ESC)
	{
		free_ressources(env->map, env);
		exit(0);
	}
	return (0);
}

