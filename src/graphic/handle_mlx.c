/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:33:08 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 17:04:53 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_env *env)
{
	if (keycode == ESC)
	{
		free_ressources(env);
		exit(0);
	}
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		env->keys[keycode] = 1;
	if (keycode == LEFT || keycode == RIGHT)
		env->keys[keycode] = 1;
	if (keycode == E && env->door_opened == 0)
	{
		env->door_opened = 1;
		env->keys[keycode] = 1;
	}
	else if (keycode == E && env->door_opened == 1)
	{
		env->door_opened = 0;
		env->keys[keycode] = 1;
	}
	else if (keycode == SPACE)
		env->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_env *env)
{
	if (keycode >= 0 && keycode < 70000)
		env->keys[keycode] = 0;
	return (0);
}

void	draw_pixel_to_image(t_env *env, int x, int y, int color)
{
	int	pixel_index;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		pixel_index = (y * env->line_length) + (x * (env->bits_per_pixel / 8));
		*(int *)(env->addr + pixel_index) = color;
	}
}

int	handle_destroy(t_env *env)
{
	free_ressources(env);
	exit(0);
	return (0);
}
