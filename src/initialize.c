/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:55:05 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/04 12:56:10 by tbellest         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keys_init(t_env *env)
{
	env->keys[A] = 0;
	env->keys[W] = 0;
	env->keys[S] = 0;
	env->keys[D] = 0;
	env->keys[LEFT] = 0;
	env->keys[RIGHT] = 0;

}

void	init_mlx(t_env	*env)
{
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		return ;
	env->win = mlx_new_window(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (env->win == NULL)
		return ;
	env->img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, \
	&env->line_length, &env->endian);
	if (env->addr == NULL)
		return ;
}

void	init_texture(t_env *env)
{
	env->texture[0] = mlx_xpm_file_to_image(env->mlx, \
		env->texture_path[0], &env->texture_width[0], &env->texture_height[0]);
	env->texture[1] = mlx_xpm_file_to_image(env->mlx, \
		env->texture_path[1], &env->texture_width[1], &env->texture_height[1]);
	env->texture[2] = mlx_xpm_file_to_image(env->mlx, \
		env->texture_path[2], &env->texture_width[2], &env->texture_height[2]);
	env->texture[3] = mlx_xpm_file_to_image(env->mlx, \
		env->texture_path[3], &env->texture_width[3], &env->texture_height[3]);
		
}