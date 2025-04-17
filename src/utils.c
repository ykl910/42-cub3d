/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:34:38 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 16:54:00 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_invalid(char *error_message, t_env *env, char *line)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_message, 2);
	get_next_line(-1);
	free_ressources(env);
	if (line)
		free(line);
	exit(1);
}

static void	free_texture_weapon(t_env *env)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (env->textures[i])
		{
			if (env->textures[i]->img)
				mlx_destroy_image(env->mlx, env->textures[i]->img);
			free(env->textures[i]);
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (env->weapon[i])
		{
			if (env->weapon[i]->img)
				mlx_destroy_image(env->mlx, env->weapon[i]->img);
			free(env->weapon[i]);
		}
		i++;
	}
}

void	free_ressources(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->map->h_max)
		free(env->map->final_map[i]);
	if (env->map->final_map)
		free(env->map->final_map);
	i = -1;
	while (++i < 8)
	{
		if (env->texture_path[i])
			free(env->texture_path[i]);
	}
	free_texture_weapon(env);
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

char	*ft_calloc_two(int count, size_t size)
{
	char	*p;
	int		i;

	i = 0;
	if (count != 0 && (count * size) / count != size)
		return (NULL);
	p = malloc((count) * size);
	if (!p)
		return (NULL);
	while (i < count - 1)
	{
		p[i] = '2';
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	color_convert(char *color, t_env *env)
{
	int		r;
	int		g;
	int		b;
	char	**temp;

	temp = ft_split(color, ',');
	if (!temp || !temp[0] || !temp[1] || !temp[2])
	{
		free_char_arr(temp);
		return (0);
	}
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	free_char_arr(temp);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_invalid("Invalid color value", env, NULL);
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}
