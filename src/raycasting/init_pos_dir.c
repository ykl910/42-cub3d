/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pos_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:12:21 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 17:01:35 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_ns(t_player *player, t_map *map, int x, int y)
{
	if (map->final_map[y][x] == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1.00001;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (map->final_map[y][x] == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1.00001;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

void	init_player_ew(t_player *player, t_map *map, int x, int y)
{
	if (map->final_map[y][x] == 'E')
	{
		player->dir_x = 1.00001;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (map->final_map[y][x] == 'W')
	{
		player->dir_x = -1.00001;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
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
			if (map->final_map[y][x] == 'N' || map->final_map[y][x] == 'S' ||
				map->final_map[y][x] == 'E' || map->final_map[y][x] == 'W')
			{
				player->pos_x = (double)x + 0.5;
				player->pos_y = (double)y + 0.5;
				init_player_ns(player, map, x, y);
				init_player_ew(player, map, x, y);
				map->final_map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
