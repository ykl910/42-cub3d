/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:42:12 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 17:11:32 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move_forward(t_player *p, t_map *m)
{
	double	move_s;
	int		next_y;
	int		next_x;

	move_s = 0.02;
	next_y = (int)(p->pos_y + p->dir_y * move_s);
	next_x = (int)(p->pos_x + p->dir_x * move_s);
	if (m->final_map[next_y][(int)p->pos_x] != '1' &&
		m->final_map[next_y][(int)p->pos_x] != 'C')
		p->pos_y += p->dir_y * move_s;
	if (m->final_map[(int)p->pos_y][next_x] != '1' &&
		m->final_map[(int)p->pos_y][next_x] != 'C')
		p->pos_x += p->dir_x * move_s;
}

void	player_move_backward(t_player *p, t_map *m)
{
	double	move_s;
	int		next_y;
	int		next_x;

	move_s = 0.02;
	next_y = (int)(p->pos_y - p->dir_y * move_s);
	next_x = (int)(p->pos_x - p->dir_x * move_s);
	if (m->final_map[next_y][(int)p->pos_x] != '1' &&
		m->final_map[next_y][(int)p->pos_x] != 'C')
		p->pos_y -= p->dir_y * move_s;
	if (m->final_map[(int)p->pos_y][next_x] != '1' &&
		m->final_map[(int)p->pos_y][next_x] != 'C')
		p->pos_x -= p->dir_x * move_s;
}

void	player_move_right(t_player *p, t_map *m)
{
	double	move_s;
	int		next_y;
	int		next_x;

	move_s = 0.02;
	next_y = (int)(p->pos_y + p->dir_x * move_s);
	next_x = (int)(p->pos_x - p->dir_y * move_s);
	if (m->final_map[next_y][(int)p->pos_x] != '1' &&
		m->final_map[next_y][(int)p->pos_x] != 'C')
		p->pos_y += p->dir_x * move_s;
	if (m->final_map[(int)p->pos_y][next_x] != '1' &&
		m->final_map[(int)p->pos_y][next_x] != 'C')
		p->pos_x -= p->dir_y * move_s;
}

void	player_move_left(t_player *p, t_map *m)
{
	double	move_s;
	int		next_y;
	int		next_x;

	move_s = 0.02;
	next_y = (int)(p->pos_y - p->dir_x * move_s);
	next_x = (int)(p->pos_x + p->dir_y * move_s);
	if (m->final_map[next_y][(int)p->pos_x] != '1' &&
		m->final_map[next_y][(int)p->pos_x] != 'C')
		p->pos_y -= p->dir_x * move_s;
	if (m->final_map[(int)p->pos_y][next_x] != '1' &&
		m->final_map[(int)p->pos_y][next_x] != 'C')
		p->pos_x += p->dir_y * move_s;
}
