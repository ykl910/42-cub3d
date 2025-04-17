/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:12:21 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 17:07:19 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_player *player, t_env *env, int x, int y)
{
	unsigned int	color;
	int				tex_index;

	while (y <= player->draw_end)
	{
		player->tex_y = (int)player->tex_pos;
		if (player->tex_y < 0)
			player->tex_y = 0;
		if (player->tex_y >= env->textures[player->side]->height)
			player->tex_y = env->textures[player->side]->height - 1;
		player->tex_pos += player->step;
		tex_index = player->tex_y * \
		(env->textures[player->side]->line_length / 4) + player->tex_x;
		color = env->textures[player->side]->data[tex_index];
		draw_pixel_to_image(env, x, y, color);
		y++;
	}
}

void	draw_ceiling_floor(t_env *env, t_player *player, int x)
{
	int	c;
	int	f;

	c = 0;
	while (c < player->draw_start)
	{
		draw_pixel_to_image(env, x, c, env->ceiling_color);
		c++;
	}
	f = player->draw_end;
	while (f < WINDOW_HEIGHT)
	{
		draw_pixel_to_image(env, x, f, env->floor_color);
		f++;
	}
}

void	raycasting(t_player *player, t_map *map, t_env *env)
{
	int		x;
	int		y;

	y = 0;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		player->hit = 0;
		player->cam_x = 2 * x / (double)WINDOW_WIDTH - 1;
		player->ray_dir_x = player->dir_x + player->plane_x * player->cam_x;
		player->ray_dir_y = player->dir_y + player->plane_y * player->cam_x;
		player->map_x = (int)player->pos_x;
		player->map_y = (int)player->pos_y;
		calculate_distance(player);
		while (player->hit == 0)
		{
			dda(player);
			add_door_side(player, map);
		}
		calculate_tex_x(player, env);
		y = calculate_line(player, env);
		draw_line(player, env, x, y);
		draw_ceiling_floor(env, player, x);
		x++;
	}
}
