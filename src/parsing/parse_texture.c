/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:35:41 by kyang             #+#    #+#             */
/*   Updated: 2025/04/22 12:15:15 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_wall_texture(char **split_line, t_env *env, int i, char *line)
{
	if (ft_strncmp(split_line[i], "NO", 2) == 0)
	{
		if (env->texture_path[3] != NULL)
			ft_invalid("Invalid texture key\n", env, line);
		env->texture_path[3] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
		env->parsed_texture++;
	}
	else if (ft_strncmp(split_line[i], "SO", 2) == 0)
	{
		if (env->texture_path[2] != NULL)
			ft_invalid("Invalid texture key\n", env, line);
		env->texture_path[2] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
		env->parsed_texture++;
	}
	else if (ft_strncmp(split_line[i], "WE", 2) == 0)
	{
		if (env->texture_path[1] != NULL)
			ft_invalid("Invalid texture key\n", env, line);
		env->texture_path[1] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
		env->parsed_texture++;
	}
	else if (ft_strncmp(split_line[i], "EA", 2) == 0)
	{
		if (env->texture_path[0] != NULL)
			ft_invalid("Invalid texture key\n ", env, line);
		env->texture_path[0] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
		env->parsed_texture++;
	}
}

void	parse_bonus_textures(char **split_line, t_env *env, int i, char *line)
{
	if (ft_strncmp(split_line[i], "DON", 3) == 0)
	{
		if (env->texture_path[4] != NULL)
			ft_invalid("Invalid texture key\n ", env, line);
		env->texture_path[4] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
		env->parsed_texture++;
	}
	else if (ft_strncmp(split_line[i], "DOE", 3) == 0)
	{
		if (env->texture_path[5] != NULL)
			ft_invalid("Invalid texture key\n ", env, line);
		env->texture_path[5] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
		env->parsed_texture++;
	}
	else if (ft_strncmp(split_line[i], "F", 1) == 0)
	{
		if (env->texture_path[6] != NULL)
			ft_invalid("Invalid texture key\n ", env, line);
		env->texture_path[6] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
		env->parsed_texture++;
	}
	else if (ft_strncmp(split_line[i], "C", 1) == 0)
	{
		if (env->texture_path[7] != NULL)
			ft_invalid("Invalid texture key\n ", env, line);
		env->texture_path[7] = ft_strndup(split_line[i + 1],
				ft_strlen(split_line[i + 1]) - 1);
		env->parsed_texture++;
	}
}

void	parse_floor_ceiling_door(char **split_line, t_env *env, int i, char *line)
{
	if (env->c == 7)
		parse_bonus_textures(split_line, env, i, line);
	else
	{
		if (ft_strncmp(split_line[i], "F", 1) == 0)
		{
			if (env->texture_path[4] != NULL)
				ft_invalid("Invalid texture key\n ", env, line);
			env->texture_path[4] = ft_strndup(split_line[i + 1],
					ft_strlen(split_line[i + 1]) - 1);
			env->parsed_texture++;
		}
		else if (ft_strncmp(split_line[i], "C", 1) == 0)
		{
			if (env->texture_path[5] != NULL)
				ft_invalid("Invalid texture key\n ", env, line);
			env->texture_path[5] = ft_strndup(split_line[i + 1],
					ft_strlen(split_line[i + 1]) - 1);
			env->parsed_texture++;
		}
	}
}

void	parse_texture(char *line, t_env *env)
{
	int		i;

	env->split_line = ft_split(line, ' ');
	if (!env->split_line)
		ft_invalid("Memory allocation failed", env, line);
	i = 0;
	while (env->split_line[i])
	{
		parse_wall_texture(env->split_line, env, i, line);
		parse_floor_ceiling_door(env->split_line, env, i, line);
		i++;
	}
	if (i > 2)
		ft_invalid("Invalid texture format", env, line);
	free_char_arr(env->split_line);
	env->split_line = NULL;
}
