/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:33:08 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/08 14:56:11 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_loop(t_env *env)
{
	if (env->keys[W])
		player_move_forward(env->player, env->map);
	if (env->keys[S])
		player_move_backward(env->player, env->map);
	if (env->keys[A])
		player_move_left(env->player, env->map);
	if (env->keys[D])
		player_move_right(env->player, env->map);
	if (env->keys[LEFT])
		player_rotate_left(env->player);
	if (env->keys[RIGHT])
		player_rotate_right(env->player);
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, \
		&env->line_length, &env->endian);
	init_player_cam(env->player, env->map, env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_env *env)
{
	if (keycode == ESC)
	{
		free_ressources(env->map, env);
		exit(0);
	}
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		env->keys[keycode] = 1;
	if (keycode == LEFT || keycode == RIGHT)
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
	free_ressources(env->map, env);
	exit(0);
	return (0);
}
