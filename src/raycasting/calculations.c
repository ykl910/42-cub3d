/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:12:21 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 17:08:04 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_distance(t_player *p)
{
	p->delta_dist_x = sqrt(1 + (p->ray_dir_y * p->ray_dir_y) / \
	(p->ray_dir_x * p->ray_dir_x));
	p->delta_dist_y = sqrt(1 + (p->ray_dir_x * p->ray_dir_x) / \
	(p->ray_dir_y * p->ray_dir_y));
	if (p->ray_dir_x < 0)
	{
		p->step_x = -1;
		p->near_dist_x = (p->pos_x - p->map_x) * p->delta_dist_x;
	}
	else
	{
		p->step_x = 1;
		p->near_dist_x = (p->map_x + 1.0 - p->pos_x) * p->delta_dist_x;
	}
	if (p->ray_dir_y < 0)
	{
		p->step_y = -1;
		p->near_dist_y = (p->pos_y - p->map_y) * p->delta_dist_y;
	}
	else
	{
		p->step_y = 1;
		p->near_dist_y = (p->map_y + 1.0 - p->pos_y) * p->delta_dist_y;
	}
}

void	dda(t_player *player)
{
	if (player->near_dist_x < player->near_dist_y)
	{
		player->near_dist_x += player->delta_dist_x;
		player->map_x += player->step_x;
		if (player->step_x == 1)
			player->side = 0;
		else
			player->side = 1;
	}
	else
	{
		player->near_dist_y += player->delta_dist_y;
		player->map_y += player->step_y;
		if (player->step_y == 1)
			player->side = 2;
		else
			player->side = 3;
	}
}

void	add_door_side(t_player *player, t_map *map)
{
	if (map->final_map[player->map_y][player->map_x] == '1' ||
		map->final_map[player->map_y][player->map_x] == 'C')
	{
		player->hit = 1;
		if (map->final_map[player->map_y][player->map_x] == 'C' &&
			(player->side == 0 || player->side == 1))
			player->side = 4;
		else if (map->final_map[player->map_y][player->map_x] == 'C' &&
			(player->side == 2 || player->side == 3))
			player->side = 5;
	}
}

void	calculate_tex_x(t_player *player, t_env *env)
{
	if (player->side == 0 || player->side == 1 || player->side == 4)
	{
		player->perp_wall_dist = (player->map_x - player->pos_x + \
				(1 - player->step_x) / 2) / player->ray_dir_x;
		player->wall_x = player->pos_y + player->perp_wall_dist * \
		player->ray_dir_y;
	}
	else
	{
		player->perp_wall_dist = (player->map_y - player->pos_y + \
				(1 - player->step_y) / 2) / player->ray_dir_y;
		player->wall_x = player->pos_x + player->perp_wall_dist * \
		player->ray_dir_x;
	}
	player->wall_x -= floor(player->wall_x);
	player->tex_x = (int)(player->wall_x * \
		(double)env->textures[player->side]->width);
	if (player->side == 1 || player->side == 2)
		player->tex_x = env->textures[player->side]->width - player->tex_x - 1;
	if (player->tex_x < 0)
		player->tex_x = 0;
	if (player->tex_x >= env->textures[player->side]->width)
		player->tex_x = env->textures[player->side]->width - 1;
}

int	calculate_line(t_player *player, t_env *env)
{
	player->line_height = (int)(WINDOW_HEIGHT / player->perp_wall_dist);
	player->draw_start = -player->line_height / 2 + WINDOW_HEIGHT / 2;
	if (player->draw_start < 0)
		player->draw_start = 0;
	player->draw_end = player->line_height / 2 + WINDOW_HEIGHT / 2;
	player->step = 1.0 * env->textures[player->side]->height / \
	player->line_height;
	player->tex_pos = (player->draw_start - WINDOW_HEIGHT / 2 + \
		player->line_height / 2) * player->step;
	if (player->draw_end >= WINDOW_HEIGHT)
		player->draw_end = WINDOW_HEIGHT - 1;
	return (player->draw_start);
}
