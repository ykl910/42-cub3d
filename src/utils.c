/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:34:38 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/08 14:41:19 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_invalid(char *error_message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_message, 2);
	exit(1);
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
		if (env->texture_path[i])
			free(env->texture_path[i]);
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

void	print_map(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->h_max)
	{
		printf("%s\n", map->final_map[y]);
		y++;
	}
}

void	*ft_calloc_two(size_t count, size_t size)
{
	void	*p;

	if (count != 0 && (count * size) / count != size)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_btwo(p, (count * size));
	return (p);
}

void	ft_btwo(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = '2';
		i++;
	}
}

