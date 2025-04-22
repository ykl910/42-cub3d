/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:35:41 by kyang             #+#    #+#             */
/*   Updated: 2025/04/22 12:49:11 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture_path(t_env *env, int index, char **split_line, char *line)
{
	if (env->texture_path[index] != NULL)
		ft_invalid("Invalid texture key\n", env, line);
	env->texture_path[index] = ft_strndup(split_line[1],
			ft_strlen(split_line[1]) - 1);
	env->parsed_texture++;
}

void	parse_wall_texture(char **split_line, t_env *env, char *line)
{
	if (ft_strncmp(split_line[0], "NO", 2) == 0)
		parse_texture_path(env, 3, split_line, line);
	else if (ft_strncmp(split_line[0], "SO", 2) == 0)
		parse_texture_path(env, 2, split_line, line);
	else if (ft_strncmp(split_line[0], "WE", 2) == 0)
		parse_texture_path(env, 1, split_line, line);
	else if (ft_strncmp(split_line[0], "EA", 2) == 0)
		parse_texture_path(env, 0, split_line, line);
}

void	parse_floor_ceiling_door(char **split_line, t_env *env, char *line)
{
	if (env->c == 7)
	{
		if (ft_strncmp(split_line[0], "DON", 3) == 0)
			parse_texture_path(env, 4, split_line, line);
		else if (ft_strncmp(split_line[0], "DOE", 3) == 0)
			parse_texture_path(env, 5, split_line, line);
		else if (ft_strncmp(split_line[0], "F", 1) == 0)
			parse_texture_path(env, 6, split_line, line);
		else if (ft_strncmp(split_line[0], "C", 1) == 0)
			parse_texture_path(env, 7, split_line, line);
	}
	else
	{
		if (ft_strncmp(split_line[0], "F", 1) == 0)
			parse_texture_path(env, 4, split_line, line);
		else if (ft_strncmp(split_line[0], "C", 1) == 0)
			parse_texture_path(env, 5, split_line, line);
	}
}

void	parse_texture(char *line, t_env *env)
{
	int		i;

	env->split_line = ft_split(line, ' ');
	if (!env->split_line)
		ft_invalid("Memory allocation failed\n", env, line);
	i = 0;
	while (env->split_line[i])
		i++;
	if (i > 2)
		ft_invalid("Invalid texture format\n", env, line);
	parse_wall_texture(env->split_line, env, line);
	parse_floor_ceiling_door(env->split_line, env, line);
	free_char_arr(env->split_line);
	env->split_line = NULL;
}
