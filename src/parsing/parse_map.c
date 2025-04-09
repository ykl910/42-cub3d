/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:28:09 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/09 13:42:12 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_delimit(t_map *map, char *file_map, t_env *env)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file_map, O_RDONLY);
	if (fd < 0)
		ft_invalid("Map invalid - no permission\n", env);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		if (env->texture_path[env->c] && line[0] != '\n')
		{
			check_map_wall(line, env);
			while(line[i])
				i++;
			if (map->w_max < i)
				map->w_max = i;
			map->h_max++;
		}
		else
		{
			if (env->c == 5)
				parse_texture(line, env);
			else
				parse_bonus_texture(line, env);
			map->map_start++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	map_parsing(t_env *env, char *file_map)
{
	int		fd;
	char	*line;
	t_map	*map;

	map = env->map;
	fd = open(file_map, O_RDONLY);
	map->final_map = ft_calloc(map->h_max, sizeof(char *));
	if (!map->final_map)
		ft_invalid("Malloc failled !\n", env);
	while (map->map_start-- > 0)
	{
		line = get_next_line(fd);
		free(line);
	}
	while (map->y < map->h_max)
	{
		map->final_map[map->y] = ft_calloc_two(map->w_max, sizeof(char));
		if (!map->final_map[map->y])
			ft_invalid("Malloc failled !\n", env);
		line = get_next_line(fd);
		map->x = -1;
		while (line[++map->x] != '\n')
		{
			if (line[map->x] != 'N' && line[map->x] != 'S' && line[map->x] != 'E' &&
				line[map->x] != 'W' && line[map->x] != '0' && line[map->x] != '1' && 
				line[map->x] != ' ' && line[map->x] != 'C')
				ft_invalid("Invalid character in map\n", env);

			if (line[map->x] == ' ')
				map->final_map[map->y][map->x] = '2';
			else
				map->final_map[map->y][map->x] = (line[map->x]);
		}
		map->final_map[map->y][map->w_max] = '\0';
		map->y++;
		free(line);
	}
	close(fd);
}

void	check_map_wall(char *line, t_env *env)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (line[i] != '1')
	{
		free(line);
		ft_invalid("map invalid - no wall\n", env);
	}
	while (line[len - 2] == ' ' && len > 1)
		len--;
	if (line[len - 2] != '1')
	{
		free(line);
		ft_invalid("map invalid - no wall\n", env);
	}
}
