/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:55:25 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 16:00:18 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*create_weapon_path(int i)
{
	char	*number;
	char	*path1;
	char	*path2;

	number = ft_itoa(i + 1);
	if (!number)
		return (NULL);
	path1 = ft_strjoin("texture/item/", number);
	if (!path1)
	{
		free(number);
		return (NULL);
	}
	path2 = ft_strjoin(path1, ".xpm");
	if (!path2)
	{
		free(path1);
		free(number);
		return (NULL);
	}
	free(path1);
	free(number);
	return (path2);
}

void	weapon_init(t_env *env)
{
	int			i;
	char		*path;

	i = -1;
	while (++i < 4)
	{
		path = create_weapon_path(i);
		if (!path)
			ft_invalid("Malloc weapon path failed\n", env, NULL);
		env->weapon[i] = malloc(sizeof(t_weapon));
		if (!env->weapon[i])
			ft_invalid("Malloc weapon failed\n", env, NULL);
		env->weapon[i]->img = mlx_xpm_file_to_image(env->mlx, \
			path, &env->weapon[i]->width, \
			&env->weapon[i]->height);
		if (!env->weapon[i]->img)
			ft_invalid("weapon loading failed\n", env, NULL);
		env->weapon[i]->data = \
			(int *)mlx_get_data_addr(env->weapon[i]->img, \
			&env->weapon[i]->bits_per_pixel, &env->weapon[i]->line_length, \
			&env->weapon[i]->endian);
		if (!env->weapon[i]->data)
			ft_invalid("weapon data loading failed\n", env, NULL);
		free(path);
	}
}

void	draw_scale_weapon(t_env *env, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < WEAPONE_SCALE)
	{
		i = 0;
		while (i < WEAPONE_SCALE)
		{
			draw_pixel_to_image(env, x + i + WINDOW_WIDTH / 2 - env->weapon[0]->width / 2,
				y + j + WINDOW_HEIGHT - env->weapon[0]->height - 650, color);
			i++;
		}
		j++;
	}
}

void	draw_weapon_frame(t_env *env, int weapon_index)
{
	int		i;
	int		j;
	int		color;
	int		offset;

	i = 0;
	while (i < env->weapon[weapon_index]->height)
	{
		j = 0;
		while (j < env->weapon[weapon_index]->width)
		{
			offset = i * (env->weapon[weapon_index]->line_length / 4) + j;
			color = env->weapon[weapon_index]->data[offset];
			if (color != 0xFFFFFF)
				draw_scale_weapon(env, j * WEAPONE_SCALE, i * WEAPONE_SCALE, color);
			j++;
		}
		i++;
	}
}

void	draw_weapon(t_env *env)
{
	int		weapon_index;

	if (env->is_shooting)
	{
		env->shooting_timer++;
		if (env->shooting_timer >= 2)
		{
			env->shooting_frame++;
			env->shooting_timer = 0;
		}
		if (env->shooting_frame >= 4)
		{
			env->shooting_frame = 0;
			env->is_shooting = 0;
		}
		weapon_index = env->shooting_frame;
	}
	else
		weapon_index = 0;
	if (weapon_index < 0 || weapon_index >= 4 || !env->weapon[weapon_index])
		return ;
	draw_weapon_frame(env, weapon_index);
}
