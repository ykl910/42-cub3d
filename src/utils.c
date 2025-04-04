/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:34:38 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/04 15:41:30 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_invalid(char *error_message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_message, 2);
	exit (1);
}

void	free_ressources(t_map *map, t_env *env)
{
	int	i;

	i = 0;
	while (i < map->h_max)
	{
		free(map->final_map[i]);
		i++;
	}
	free(map->final_map);
	i = 0;
	while (i < 6)
	{
		if (map->texture[i])
			free(map->texture[i]);
		i++;
	}
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
	{
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
}

void	free_char_arr(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}
