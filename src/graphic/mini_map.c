/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:33:02 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 17:00:53 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_env *env, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < MINIMAP_SCALE)
	{
		i = 0;
		while (i < MINIMAP_SCALE)
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
				draw_square(env, x * MINIMAP_SCALE, y * \
				MINIMAP_SCALE, 0x222222);
			else if (env->map->final_map[y - 5][x - 5] == '0')
				draw_square(env, x * MINIMAP_SCALE, y * \
				MINIMAP_SCALE, 0xDDDDDD);
			else if (env->map->final_map[y - 5][x - 5] == 'C')
				draw_square(env, x * MINIMAP_SCALE, y * \
				MINIMAP_SCALE, RED);
			else if (env->map->final_map[y - 5][x - 5] == 'O')
				draw_square(env, x * MINIMAP_SCALE, y * \
				MINIMAP_SCALE, GREEN);
			x++;
		}
		y++;
	}
}

void	draw_player_on_minimap(t_env *env)
{
	int	px;
	int	py;

	px = (env->player->pos_x + 5) * MINIMAP_SCALE;
	py = (env->player->pos_y + 5) * MINIMAP_SCALE;
	draw_square(env, px - 1, py - 1, 0xFF0000);
}

void	draw_ray_on_minimap(t_env *env, float ray_x, float ray_y, float step)
{
	int		map_x;
	int		map_y;
	int		px;
	int		py;
	int		max_steps;

	max_steps = (int)(5.0 / step);
	while (max_steps--)
	{
		ray_x += env->player->dir_x * step;
		ray_y += env->player->dir_y * step;
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (map_x < 0 || map_y < 0 || map_y >= \
		env->map->h_max || map_x >= env->map->w_max)
			break ;
		if (env->map->final_map[map_y][map_x] == '1' ||
			env->map->final_map[map_y][map_x] == 'C')
			break ;
		px = (ray_x + 5) * MINIMAP_SCALE;
		py = (ray_y + 5) * MINIMAP_SCALE;
		draw_square(env, px - 1, py - 1, BLUE);
	}
}

void	draw_player_dir_on_minimap(t_env *env)
{
	float	ray_x;
	float	ray_y;
	float	step;
	int		px;
	int		py;

	ray_x = env->player->pos_x;
	ray_y = env->player->pos_y;
	step = 0.05;
	draw_ray_on_minimap(env, ray_x, ray_y, step);
	px = (env->player->pos_x + 5) * MINIMAP_SCALE;
	py = (env->player->pos_y + 5) * MINIMAP_SCALE;
	draw_square(env, px - 1, py - 1, RED);
}
