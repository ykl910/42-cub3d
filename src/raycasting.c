/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:12:21 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/07 17:25:06 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				player->posX = (double)x;
				player->posY = (double)y;
				if (map->final_map[y][x] == 'N')
				{
					player->dirX = 0;
					player->dirY = -1;
					player->planeX = 0.66;
					player->planeY = 0;
				}
				else if (map->final_map[y][x] == 'S')
				{
					player->dirX = 0;
					player->dirY = 1;
					player->planeX = -0.66;
					player->planeY = 0;
				}
				else if (map->final_map[y][x] == 'E')
				{
					player->dirX = 1;
					player->dirY = 0;
					player->planeX = 0;
					player->planeY = 0.66;

				}
				else if (map->final_map[y][x] == 'W')
				{
					player->dirX = -1;
					player->dirY = 0;
					player->planeX = 0;
					player->planeY = -0.66;
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
	while (x < WINDOW_WIDTH)
	{
		player->hit = 0;
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
			if (map->final_map[player->mapY][player->mapX] == '1')
				player->hit = 1;
		}
		if(player->side == 0 || player->side == 1)
			player->perpWallDist = (player->nearDistX - player->deltaDistX);
		else
			player->perpWallDist = (player->nearDistY - player->deltaDistY);
		if (player->side == 0 || player->side == 1)
			player->wallX = player->posY + player->perpWallDist * player->rayDirY;
		else
			player->wallX = player->posX + player->perpWallDist * player->rayDirX;
		player->wallX -= floor(player->wallX);

		// calcul texX
		player->texX = (int)(player->wallX * (double)env->textures[player->side]->width);

		// inversion selon direction
		if (player->side == 1 || player->side == 2)
			player->texX = env->textures[player->side]->width - player->texX - 1;

		// clamp
		if (player->texX < 0)
			player->texX = 0;
		if (player->texX >= env->textures[player->side]->width)
			player->texX = env->textures[player->side]->width - 1;

		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!

		//Calculate height of line to draw on screen
		player->lineHeight = (int)(WINDOW_HEIGHT / player->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		player->drawStart = -player->lineHeight / 2 + WINDOW_HEIGHT / 2;
		if(player->drawStart < 0)
			player->drawStart = 0;
		player->drawEnd = player->lineHeight / 2 + WINDOW_HEIGHT / 2;
		double step = 1.0 * env->textures[player->side]->height / player->lineHeight;
		double texPos = (player->drawStart - WINDOW_HEIGHT / 2 + player->lineHeight / 2) * step;
		if(player->drawEnd >= WINDOW_HEIGHT)
			player->drawEnd = WINDOW_HEIGHT - 1;

		y = player->drawStart;
		unsigned int color;
		while (y <= player->drawEnd)
		{
			// player->texY = (int)texPos & (env->textures[player->side]->height - 1); // attention à la taille puissance de 2
			player->texY = (int)texPos;
			if (player->texY < 0)
				player->texY = 0;
			if (player->texY >= env->textures[player->side]->height)
				player->texY = env->textures[player->side]->height - 1;
			texPos += step;
			int tex_index = player->texY * (env->textures[player->side]->line_length / 4) + player->texX;
			color = env->textures[player->side]->data[tex_index];
			// Sombre les murs selon leur côté (facultatif, mais classique dans raycasters)
			// if (player->side == 1 || player->side == 3)
				// color = (color >> 1) & 0x7F7F7F;
			draw_pixel_to_image(env, x, y, color);
			y++;
		}
		x++;
		//printf("x = %d\n", x);
	}
}
