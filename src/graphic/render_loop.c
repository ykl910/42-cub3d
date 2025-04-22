/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:06:10 by kyang             #+#    #+#             */
/*   Updated: 2025/04/22 12:18:45 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keyboard_move(t_env *env)
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
	if (env->keys[E])
		open_door(env);
	if (env->keys[R])
		close_door(env);
	if (env->keys[SPACE])
	{
		if (!env->is_shooting)
		{
			env->is_shooting = 1;
			env->shooting_frame = 0;
			env->shooting_timer = 0;
		}
	}
}

int	render_loop(t_env *env)
{
	keyboard_move(env);
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, \
		&env->line_length, &env->endian);
	raycasting(env->player, env->map, env);
	if (env->c == 7)
	{
		draw_minimap(env);
		draw_weapon(env);
		draw_player_on_minimap(env);
		draw_player_dir_on_minimap(env);
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
