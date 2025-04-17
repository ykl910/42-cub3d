/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:55:05 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 16:44:39 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map, t_env *env, char *file_map)
{
	int	i;

	i = -1;
	if (ft_strnstr(file_map, "bonus", ft_strlen(file_map)))
		env->c = 7;
	else
		env->c = 5;
	map->x = 0;
	map->y = 0;
	map->h_max = 0;
	map->w_max = 0;
	map->map_start = 0;
	map->started_map = 0;
	map->final_map = NULL;
	while (++i < 8)
		env->texture_path[i] = NULL;
	i = -1;
	while (++i < 6)
		env->textures[i] = NULL;
	i = -1;
	while (++i < 4)
		env->weapon[i] = NULL;
}

void	init_env(t_env *env)
{
	env->keys[A] = 0;
	env->keys[W] = 0;
	env->keys[S] = 0;
	env->keys[D] = 0;
	env->keys[E] = 0;
	env->keys[SPACE] = 0;
	env->keys[LEFT] = 0;
	env->keys[RIGHT] = 0;
	env->door_opened = 0;
	env->player_count = 0;
	env->is_shooting = 0;
	env->shooting_frame = 0;
	env->shooting_timer = 0;
	env->parsed_texture = 0;
	env->img = NULL;
	env->addr = NULL;
	env->mlx = NULL;
	env->win = NULL;
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
			ft_invalid("Malloc texture failed\n", env, NULL);
		env->textures[i]->img = mlx_xpm_file_to_image(env->mlx, \
			env->texture_path[i], &env->textures[i]->width, \
			&env->textures[i]->height);
		if (!env->textures[i]->img)
			ft_invalid("Texture loading failed\n", env, NULL);
		env->textures[i]->data = \
			(int *)mlx_get_data_addr(env->textures[i]->img, \
			&env->textures[i]->bits_per_pixel, &env->textures[i]->line_length, \
			&env->textures[i]->endian);
		if (!env->textures[i]->data)
			ft_invalid("Texture data loading failed\n", env, NULL);
		i++;
	}
	env->ceiling_color = color_convert(env->texture_path[env->c], env);
	env->floor_color = color_convert(env->texture_path[env->c - 1], env);
}
