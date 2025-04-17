/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:35:41 by kyang             #+#    #+#             */
/*   Updated: 2025/04/17 15:40:48 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_wall_texture(char **split_line, t_env *env, int i)
{
	if (ft_strncmp(split_line[i], "NO", 2) == 0)
		env->texture_path[3] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
	else if (ft_strncmp(split_line[i], "SO", 2) == 0)
		env->texture_path[2] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
	else if (ft_strncmp(split_line[i], "WE", 2) == 0)
		env->texture_path[1] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
	else if (ft_strncmp(split_line[i], "EA", 2) == 0)
		env->texture_path[0] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
}

void	parse_floor_ceiling_door(char **split_line, t_env *env, int i)
{
	if (env->bonus)
	{
		if (ft_strncmp(split_line[i], "DON", 3) == 0)
			env->texture_path[4] = ft_strndup(split_line[i + 1],
					ft_strlen(split_line[i + 1]) - 1);
		else if (ft_strncmp(split_line[i], "DOE", 3) == 0)
			env->texture_path[5] = ft_strndup(split_line[i + 1],
					ft_strlen(split_line[i + 1]) - 1);
		else if (ft_strncmp(split_line[i], "F", 1) == 0)
			env->texture_path[6] = ft_strndup(split_line[i + 1],
					ft_strlen(split_line[i + 1]) - 1);
		else if (ft_strncmp(split_line[i], "C", 1) == 0)
			env->texture_path[7] = ft_strndup(split_line[i + 1],
					ft_strlen(split_line[i + 1]) - 1);
	}
	else
	{
		if (ft_strncmp(split_line[i], "F", 1) == 0)
			env->texture_path[4] = ft_strndup(split_line[i + 1],
					ft_strlen(split_line[i + 1]) - 1);
		else if (ft_strncmp(split_line[i], "C", 1) == 0)
			env->texture_path[5] = ft_strndup(split_line[i + 1],
					ft_strlen(split_line[i + 1]) - 1);
	}
}

void	parse_texture(char *line, t_env *env)
{
	char	**split_line;
	int		i;

	split_line = ft_split(line, ' ');
	if (!split_line)
		ft_invalid("Memory allocation failed", env, line);
	i = 0;
	while (split_line[i])
	{
		parse_wall_texture(split_line, env, i);
		parse_floor_ceiling_door(split_line, env, i);
		i++;
	}
	if (i > 2)
	{
		free_char_arr(split_line);
		ft_invalid("Invalid texture format", env, line);
	}
	free_char_arr(split_line);
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
