/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:32:31 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/04 12:45:21 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_rotate_left(t_player *player)
{
	double	moveSpeed;
	double oldDirX;
	double oldPlaneX;

	moveSpeed = 0.02;
	oldDirX = player->dirX;
	player->dirX = player->dirX * cos(-moveSpeed) - player->dirY * sin(-moveSpeed);
	player->dirY = oldDirX * sin(-moveSpeed) + player->dirY * cos(-moveSpeed);
	oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(-moveSpeed) - player->planeY * sin(-moveSpeed);
	player->planeY = oldPlaneX * sin(-moveSpeed) + player->planeY * cos(-moveSpeed);
}

void	player_rotate_right(t_player *player)
{
	double	moveSpeed;
	double oldDirX;
	double oldPlaneX;

	moveSpeed = 0.02;
	oldDirX = player->dirX;
	player->dirX = player->dirX * cos(moveSpeed) - player->dirY * sin(moveSpeed);
	player->dirY = oldDirX * sin(moveSpeed) + player->dirY * cos(moveSpeed);
	oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(moveSpeed) - player->planeY * sin(moveSpeed);
	player->planeY = oldPlaneX * sin(moveSpeed) + player->planeY * cos(moveSpeed);
}
