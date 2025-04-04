/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:34:38 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/04 15:00:11 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_invalid(char *error_message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", error_message);
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
