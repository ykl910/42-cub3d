/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:12:21 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/09 17:09:08 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_player *player, t_env *env, int x, int y)
{
	unsigned int	color;
	int				tex_index;

	while (y <= player->drawEnd)
	{
		//player->texY = (int)texPos & (env->textures[player->side]->height - 1); // attention à la taille puissance de 2
		player->texY = (int)player->texPos;
		if (player->texY < 0)
			player->texY = 0;
		if (player->texY >= env->textures[player->side]->height)
			player->texY = env->textures[player->side]->height - 1;
		player->texPos += player->step;
		tex_index = player->texY * \
		(env->textures[player->side]->line_length / 4) + player->texX;
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
	while (c < player->drawStart)
	{
		draw_pixel_to_image(env, x, c, env->ceiling_color);
		c++;
	}
	f = player->drawEnd;
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
		player->camX = 2 * x / (double)WINDOW_WIDTH - 1;
		player->rayDirX = player->dirX + player->planeX * player->camX;
		player->rayDirY = player->dirY + player->planeY * player->camX;
		player->mapX = (int)player->posX;
		player->mapY = (int)player->posY;
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
