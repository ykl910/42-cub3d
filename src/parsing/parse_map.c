/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:28:09 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/17 12:59:21 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_map_line(t_map *map, char *line)
{
	int	i;

	i = 0;
	if (map->started_map == 0)
		map->started_map = 1;
	while (line[i])
		i++;
	if (map->w_max < i)
		map->w_max = i;
	map->h_max++;
}

void	map_delimit(t_map *map, char *file_map, t_env *env)
{
	int		fd;
	char	*line;
	char 	*tmp;

	tmp = ft_strrchr(file_map, '.');
	if (ft_strcmp(ft_strrchr(file_map, '.'), ".cub"))
		ft_invalid("Map invalid - wrong externsion\n", env);
	fd = open(file_map, O_RDONLY);
	if (fd < 0)
		ft_invalid("Map invalid - no permission\n", env);
	line = get_next_line(fd);
	while (line)
	{
		if (env->texture_path[env->c] && line[0] != '\n')
			process_map_line(map, line);
		else
		{
			if (line[0] != '\n')
				parse_texture(line, env);
			if (map->started_map == 0)
				map->map_start++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	parse_map_line_content(t_env *env, t_map *map, char *line)
{
	map->x = -1;
	while (line[++map->x] != '\0' && line[map->x] != '\n')
	{
		if (line[map->x] != 'N' && line[map->x] != 'S' && line[map->x] != 'E' &&
			line[map->x] != 'W' && line[map->x] != '0' && line[map->x] != '1' &&
			line[map->x] != ' ' && line[map->x] != 'C')
			ft_invalid("Invalid character in map\n", env);
		if (line[map->x] == 'C' && !env->bonus)
			ft_invalid("Invalid character in map\n", env);
		if (line[map->x] == 'N' || line[map->x] == 'S' ||
			line[map->x] == 'E' || line[map->x] == 'W')
		{
			env->player_count++;
			if (env->player_count > 1)
				ft_invalid("Invalid character in map\n", env);
		}
		if (line[map->x] == ' ')
			map->final_map[map->y][map->x] = '2';
		else
			map->final_map[map->y][map->x] = line[map->x];
	}
	// get_next_line(-1);
	//map->final_map[map->y][map->w_max] = '\0';
}

static void	fill_map(t_env *env, t_map *map, int fd)
{
	char	*line;

	while (map->y < map->h_max)
	{
		map->final_map[map->y] = ft_calloc_two(map->w_max + 1, sizeof(char));
		if (!map->final_map[map->y])
			ft_invalid("Malloc failled !\n", env);
		line = get_next_line(fd);

		parse_map_line_content(env, map, line);
		map->y++;
		free(line);
	}
	if (env->player_count == 0)
		ft_invalid("No player in map\n", env);
	//get_next_line(-1);
	check_map_closed_and_connected(env);
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
	fill_map(env, map, fd);
	get_next_line(-1);
	close(fd);
}
