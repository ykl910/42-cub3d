/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:35:41 by kyang             #+#    #+#             */
/*   Updated: 2025/04/04 15:31:34 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture(t_map *map, char *line)
{
	char	**split_line;
	int		i;

	split_line = ft_split(line, ' ');
	if (!split_line)
		ft_invalid("Memory allocation failed");
	i = 0;
	while (split_line[i])
	{
		if (ft_strncmp(split_line[i], "NO", 2) == 0)
			map->texture[0] = ft_strdup(split_line[i + 1]);
		else if (ft_strncmp(split_line[i], "SO", 2) == 0)
			map->texture[1] = ft_strdup(split_line[i + 1]);
		else if (ft_strncmp(split_line[i], "WE", 2) == 0)
			map->texture[2] = ft_strdup(split_line[i + 1]);
		else if (ft_strncmp(split_line[i], "EA", 2) == 0)
			map->texture[3] = ft_strdup(split_line[i + 1]);
		else if (ft_strncmp(split_line[i], "F", 1) == 0)
			map->texture[4] = ft_strdup(split_line[i + 1]);
		else if (ft_strncmp(split_line[i], "C", 1) == 0)
			map->texture[5] = ft_strdup(split_line[i + 1]);
		i++;
	}
	free_char_arr(split_line);
}
