/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:42:12 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/09 13:50:34 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move_forward(t_player *player, t_map *map)
{
	double	moveSpeed;

	moveSpeed = 0.02;
	if (map->final_map[(int)(player->posY + player->dirY * moveSpeed)][(int)player->posX] != '1' &&
		map->final_map[(int)(player->posY + player->dirY * moveSpeed)][(int)player->posX] != 'C')
		player->posY += player->dirY * moveSpeed;
	if (map->final_map[(int)player->posY][(int)(player->posX + player->dirX * moveSpeed)] != '1' &&
		map->final_map[(int)player->posY][(int)(player->posX + player->dirX * moveSpeed)] != 'C')
		player->posX += player->dirX * moveSpeed;
}

void	player_move_backward(t_player *player, t_map *map)
{
	double	moveSpeed;

	moveSpeed = 0.02;
	if (map->final_map[(int)(player->posY - player->dirY * moveSpeed)][(int)player->posX] != '1' &&
		map->final_map[(int)(player->posY - player->dirY * moveSpeed)][(int)player->posX] != 'C')
		player->posY -= player->dirY * moveSpeed;
	if (map->final_map[(int)player->posY][(int)(player->posX - player->dirX * moveSpeed)] != '1' &&
		map->final_map[(int)player->posY][(int)(player->posX - player->dirX * moveSpeed)] != 'C')
		player->posX -= player->dirX * moveSpeed;
}

void	player_move_right(t_player *player, t_map *map)
{
	double	moveSpeed;

	moveSpeed = 0.02;
	if (map->final_map[(int)(player->posY + player->dirX * moveSpeed)][(int)player->posX] != '1' &&
		map->final_map[(int)(player->posY + player->dirX * moveSpeed)][(int)player->posX] != 'C')
		player->posY += player->dirX * moveSpeed;
	if (map->final_map[(int)player->posY][(int)(player->posX - player->dirY * moveSpeed)] != '1' &&
		map->final_map[(int)player->posY][(int)(player->posX - player->dirY * moveSpeed)] != 'C')
		player->posX -= player->dirY * moveSpeed;
}

void	player_move_left(t_player *player, t_map *map)
{
	double	moveSpeed;

	moveSpeed = 0.02;
	if (map->final_map[(int)(player->posY - player->dirX * moveSpeed)][(int)player->posX] != '1' &&
		map->final_map[(int)(player->posY - player->dirX * moveSpeed)][(int)player->posX] != 'C')
		player->posY -= player->dirX * moveSpeed;
	if (map->final_map[(int)player->posY][(int)(player->posX + player->dirY * moveSpeed)] != '1' &&
		map->final_map[(int)player->posY][(int)(player->posX + player->dirY * moveSpeed)] != 'C')
		player->posX += player->dirY * moveSpeed;
}
