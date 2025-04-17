/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:32:31 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 17:08:26 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_rotate_left(t_player *player)
{
	double	move_s;
	double	old_dirx;
	double	old_planex;

	move_s = 0.02;
	old_dirx = player->dir_x;
	player->dir_x = player->dir_x * cos(-move_s) - player->dir_y * sin(-move_s);
	player->dir_y = old_dirx * sin(-move_s) + player->dir_y * cos(-move_s);
	old_planex = player->plane_x;
	player->plane_x = player->plane_x * cos(-move_s) - \
	player->plane_y * sin(-move_s);
	player->plane_y = old_planex * sin(-move_s) + player->plane_y * \
	cos(-move_s);
}

void	player_rotate_right(t_player *player)
{
	double	move_s;
	double	old_dirx;
	double	old_planex;

	move_s = 0.02;
	old_dirx = player->dir_x;
	player->dir_x = player->dir_x * cos(move_s) - player->dir_y * sin(move_s);
	player->dir_y = old_dirx * sin(move_s) + player->dir_y * cos(move_s);
	old_planex = player->plane_x;
	player->plane_x = player->plane_x * cos(move_s) - \
	player->plane_y * sin(move_s);
	player->plane_y = old_planex * sin(move_s) + player->plane_y * cos(move_s);
}

static void	player_rotate(t_player *player, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dir_x;
	old_planex = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dirx * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y * \
	sin(angle);
	player->plane_y = old_planex * sin(angle) + player->plane_y * cos(angle);
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
