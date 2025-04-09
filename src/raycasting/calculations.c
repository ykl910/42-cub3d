/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:12:21 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/09 17:13:26 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_distance(t_player *p)
{
	p->deltaDistX = sqrt(1 + (p->rayDirY * p->rayDirY) / \
	(p->rayDirX * p->rayDirX));
	p->deltaDistY = sqrt(1 + (p->rayDirX * p->rayDirX) / \
	(p->rayDirY * p->rayDirY));
	if (p->rayDirX < 0)
	{
		p->stepX = -1;
		p->nearDistX = (p->posX - p->mapX) * p->deltaDistX;
	}
	else
	{
		p->stepX = 1;
		p->nearDistX = (p->mapX + 1.0 - p->posX) * p->deltaDistX;
	}
	if (p->rayDirY < 0)
	{
		p->stepY = -1;
		p->nearDistY = (p->posY - p->mapY) * p->deltaDistY;
	}
	else
	{
		p->stepY = 1;
		p->nearDistY = (p->mapY + 1.0 - p->posY) * p->deltaDistY;
	}
}

void	dda(t_player *player)
{
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
}

void	add_door_side(t_player *player, t_map *map)
{
	if (map->final_map[player->mapY][player->mapX] == '1' ||
		map->final_map[player->mapY][player->mapX] == 'C')
	{
		player->hit = 1;
		if (map->final_map[player->mapY][player->mapX] == 'C' &&
			(player->side == 0 || player->side == 1))
			player->side = 4;
		else if (map->final_map[player->mapY][player->mapX] == 'C' &&
			(player->side == 2 || player->side == 3))
			player->side = 5;
	}
}

void	calculate_tex_x(t_player *player, t_env *env)
{
	if (player->side == 0 || player->side == 1 || player->side == 4)
	{
		player->perpWallDist = (player->mapX - player->posX + \
				(1 - player->stepX) / 2) / player->rayDirX;
		player->wallX = player->posY + player->perpWallDist * player->rayDirY;
	}
	else
	{
		player->perpWallDist = (player->mapY - player->posY + \
				(1 - player->stepY) / 2) / player->rayDirY;
		player->wallX = player->posX + player->perpWallDist * player->rayDirX;
	}
	player->wallX -= floor(player->wallX);
	player->texX = (int)(player->wallX * \
		(double)env->textures[player->side]->width);
	if (player->side == 1 || player->side == 2)
		player->texX = env->textures[player->side]->width - player->texX - 1;
	if (player->texX < 0)
		player->texX = 0;
	if (player->texX >= env->textures[player->side]->width)
		player->texX = env->textures[player->side]->width - 1;
}

int	calculate_line(t_player *player, t_env *env)
{
	player->lineHeight = (int)(WINDOW_HEIGHT / player->perpWallDist);
	player->drawStart = -player->lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (player->drawStart < 0)
		player->drawStart = 0;
	player->drawEnd = player->lineHeight / 2 + WINDOW_HEIGHT / 2;
	player->step = 1.0 * env->textures[player->side]->height / \
	player->lineHeight;
	player->texPos = (player->drawStart - WINDOW_HEIGHT / 2 + \
		player->lineHeight / 2) * player->step;
	if (player->drawEnd >= WINDOW_HEIGHT)
		player->drawEnd = WINDOW_HEIGHT - 1;
	return (player->drawStart);
}
