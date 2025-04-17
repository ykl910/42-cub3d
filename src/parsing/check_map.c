/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:10:33 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 15:36:53 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	neighbours_is_full(char **map, int y, int x, t_env *env)
{
	if (y <= 0 || y >= env->map->h_max - 1 || x <= 0 || x >= env->map->w_max - 1)
		ft_invalid("Map not closed (border reached)\n", env, NULL);
	if (map[y + 1][x] == '2')
		ft_invalid("Map not closed (void space)\n", env, NULL);
	if (map[y - 1][x] == '2')
		ft_invalid("Map not closed (void space)\n", env, NULL);
	if (map[y][x + 1] == '2')
		ft_invalid("Map not closed (void space)\n", env, NULL);
	if (map[y][x - 1] == '2')
		ft_invalid("Map not closed (void space)\n", env, NULL);
}

void	check_map_closed_and_connected(t_env *env)
{
	t_map	*map;
	int		x;
	int		y;

	x = 0;
	y = 0;
	map = env->map;
	while (y < map->h_max)
	{
		x = 0;
		while (x < map->w_max)
		{
			if (map->final_map[y][x] == '0' || map->final_map[y][x] == 'N' || map->final_map[y][x] == 'S' || map->final_map[y][x] == 'E' \
				|| map->final_map[y][x] == 'W'  || map->final_map[y][x] == 'C')
			{
				neighbours_is_full(map->final_map, y, x, env);
			}
			x++;
		}
		y++;
	}
}
