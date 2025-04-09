/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:54:26 by kyang             #+#    #+#             */
/*   Updated: 2025/04/09 14:35:30 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_env *env)
{
	int x;
	int y;
	
	x = (int)env->player->posX;
	y = (int)env->player->posY;
	if (env->map->final_map[y][x] == 'C')
		env->map->final_map[y][x] = 'O';
	else if (env->map->final_map[y + 1][x] == 'C')
		env->map->final_map[y + 1][x] = 'O';
	else if (env->map->final_map[y][x + 1] == 'C')
		env->map->final_map[y][x + 1] = 'O';
	else if (env->map->final_map[y - 1][x] == 'C')
		env->map->final_map[y - 1][x] = 'O';
	else if (env->map->final_map[y][x - 1] == 'C')
		env->map->final_map[y][x - 1] = 'O';
}

void	close_door(t_env *env)
{
	int x;
	int y;
	
	x = (int)env->player->posX;
	y = (int)env->player->posY;
	if (env->map->final_map[y + 1][x] == 'O')
		env->map->final_map[y + 1][x] = 'C';
	else if (env->map->final_map[y][x + 1] == 'O')
		env->map->final_map[y][x + 1] = 'C';
	else if (env->map->final_map[y - 1][x] == 'O')
		env->map->final_map[y - 1][x] = 'C';
	else if (env->map->final_map[y][x - 1] == 'O')
		env->map->final_map[y][x - 1] = 'C';
}
