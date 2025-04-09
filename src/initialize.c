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

void	map_init(t_map *map, t_env *env, char *file_map)
{
	int	i;

	i = 0;
	if (ft_strnstr(file_map, "bonus", ft_strlen(file_map)))
	{
		env->bonus = 1;
		env->c = 7;
	}
	else
	{
		env->bonus = 0;
		env->c = 5;
	}
	map->x = 0;
	map->y = 0;
	map->h_max = 0;
	map->w_max = 0;
	map->map_start = 0;
	map->final_map = NULL;
	while (i < 8)
	{
		env->texture_path[i] = NULL;
		i++;
	}
}

void	keys_init(t_env *env)
{
	env->keys[A] = 0;
	env->keys[W] = 0;
	env->keys[S] = 0;
	env->keys[D] = 0;
	env->keys[SPACE] = 0;
	env->keys[LEFT] = 0;
	env->keys[RIGHT] = 0;
	env->door_opened = 0;
}

void	init_mlx(t_env	*env)
{
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		return ;
	env->win = mlx_new_window(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
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
	int			i;

	i = 0;
	while (i < env->c - 1)
	{
		env->textures[i] = malloc(sizeof(t_texture));
		if (!env->textures[i])
			ft_invalid("Malloc texture failed\n", env);
		env->textures[i]->img = mlx_xpm_file_to_image(env->mlx, \
			env->texture_path[i], &env->textures[i]->width, &env->textures[i]->height);
		if (!env->textures[i]->img)
			ft_invalid("Texture loading failed\n", env);
		env->textures[i]->data = (int *)mlx_get_data_addr(env->textures[i]->img, \
			&env->textures[i]->bits_per_pixel, &env->textures[i]->line_length, \
			&env->textures[i]->endian);
		if (!env->textures[i]->data)
			ft_invalid("Texture data loading failed\n", env);
		i++;
	}
	env->ceiling_color = color_convert(env->texture_path[env->c]);
	env->floor_color = color_convert(env->texture_path[env->c - 1]);
}
