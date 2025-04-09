/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:42:12 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/09 15:22:43 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move_forward(t_player *p, t_map *m)
{
	double	move_s;

	move_s = 0.02;
	if (m->final_map[(int)(p->posY + p->dirY * move_s)][(int)p->posX] != '1' &&
		m->final_map[(int)(p->posY + p->dirY * move_s)][(int)p->posX] != 'C')
		p->posY += p->dirY * move_s;
	if (m->final_map[(int)p->posY][(int)(p->posX + p->dirX * move_s)] != '1' &&
		m->final_map[(int)p->posY][(int)(p->posX + p->dirX * move_s)] != 'C')
		p->posX += p->dirX * move_s;
}

void	player_move_backward(t_player *p, t_map *m)
{
	double	move_s;

	move_s = 0.02;
	if (m->final_map[(int)(p->posY - p->dirY * move_s)][(int)p->posX] != '1' &&
		m->final_map[(int)(p->posY - p->dirY * move_s)][(int)p->posX] != 'C')
		p->posY -= p->dirY * move_s;
	if (m->final_map[(int)p->posY][(int)(p->posX - p->dirX * move_s)] != '1' &&
		m->final_map[(int)p->posY][(int)(p->posX - p->dirX * move_s)] != 'C')
		p->posX -= p->dirX * move_s;
}

void	player_move_right(t_player *p, t_map *m)
{
	double	move_s;

	move_s = 0.02;
	if (m->final_map[(int)(p->posY + p->dirX * move_s)][(int)p->posX] != '1' &&
		m->final_map[(int)(p->posY + p->dirX * move_s)][(int)p->posX] != 'C')
		p->posY += p->dirX * move_s;
	if (m->final_map[(int)p->posY][(int)(p->posX - p->dirY * move_s)] != '1' &&
		m->final_map[(int)p->posY][(int)(p->posX - p->dirY * move_s)] != 'C')
		p->posX -= p->dirY * move_s;
}

void	player_move_left(t_player *p, t_map *m)
{
	double	move_s;

	move_s = 0.02;
	if (m->final_map[(int)(p->posY - p->dirX * move_s)][(int)p->posX] != '1' &&
		m->final_map[(int)(p->posY - p->dirX * move_s)][(int)p->posX] != 'C')
		p->posY -= p->dirX * move_s;
	if (m->final_map[(int)p->posY][(int)(p->posX + p->dirY * move_s)] != '1' &&
		m->final_map[(int)p->posY][(int)(p->posX + p->dirY * move_s)] != 'C')
		p->posX += p->dirY * move_s;
}
