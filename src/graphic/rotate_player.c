/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:32:31 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/08 14:56:16 by tbellest         ###   ########.fr       */
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

static void	player_rotate(t_player *player, double angle)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = player->dirX;
	oldPlaneX = player->planeX;
	player->dirX = player->dirX * cos(angle) - player->dirY * sin(angle);
	player->dirY = oldDirX * sin(angle) + player->dirY * cos(angle);
	player->planeX = player->planeX * cos(angle) - player->planeY * sin(angle);
	player->planeY = oldPlaneX * sin(angle) + player->planeY * cos(angle);
}

int	mouse_move(int x, int y, t_env *env)
{
	static int	last_x;
	int			delta_x;
	double		angle;

	(void) y;
	last_x = WINDOW_WIDTH / 2;
	delta_x = x - last_x;
	if (delta_x != 0)
	{
		angle = delta_x * 0.0005;
		player_rotate(env->player, angle);
	}
	mlx_mouse_move(env->mlx, env->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	last_x = WINDOW_WIDTH / 2;
	return (0);
}
