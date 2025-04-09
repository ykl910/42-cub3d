/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:33:02 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/09 14:36:46 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_env *env, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while(j < MINIMAP_SCALE)
	{
		i = 0;
		while(i < MINIMAP_SCALE)
		{
			draw_pixel_to_image(env, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_minimap(t_env *env)
{
	int	x;
	int	y;

	y = 5;
	while (y < env->map->h_max + 5)
	{
		x = 5;
		while (x < env->map->w_max + 5)
		{
			if (env->map->final_map[y - 5][x - 5] == '1')
				draw_square(env, x * MINIMAP_SCALE, y * MINIMAP_SCALE, 0x000000);
			else
				draw_square(env, x * MINIMAP_SCALE, y * MINIMAP_SCALE, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	draw_player_on_minimap(t_env *env)
{
	int	px;
	int	py;

	px = (env->player->posX + 5) * MINIMAP_SCALE;
	py = (env->player->posY + 5) * MINIMAP_SCALE;

	draw_square(env, px - 1, py - 1, 0xFF0000);
}
