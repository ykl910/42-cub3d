/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:28:09 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/04 16:19:40 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_init(t_map *map)
{
	int	i;

	i = 0;
	map->x = 0;
	map->y = 0;
	map->h_max = 0;
	map->w_max = 0;
	map->map_start = 0;
	map->final_map = NULL;
	while (i < 6)
	{
		map->texture[i] = NULL;
		i++;
	}
}

void	map_delimit(t_map *map, char *file_map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file_map, O_RDONLY);
	if (fd < 0)
		ft_invalid("Map invalid - no permission\n");
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		if (map->texture[5] && line[0] != '\n')
		{
			check_map_wall(line);
			while(line[i])
				i++;
			if (map->w_max < i)
				map->w_max = i;
			map->h_max++;
		}
		else
		{
			parse_texture(map, line);
			map->map_start++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	map_parsing(t_map *map, char *file_map)
{
	int		fd;
	char	*line;

	fd = open(file_map, O_RDONLY);
	map->final_map = ft_calloc_two(map->h_max, sizeof(char *));
	if (!map->final_map)
		ft_invalid("Malloc failled !\n");
	//printf("%d\n", map->map_start);
	while (map->map_start-- > 0)
	{
		line = get_next_line(fd);
		free(line);
	}
	//printf("%d\n", map->h_max);
	//printf("%d", map->w_max);
	while (map->y < map->h_max)
	{
		map->final_map[map->y] = ft_calloc_two(map->w_max, sizeof(char));
		if (!map->final_map[map->y])
			ft_invalid("Malloc failled !\n");
		line = get_next_line(fd);
		map->x = -1;
		while (line[++map->x] != '\n')
		{
			if (line[map->x] != 'N' && line[map->x] != 'S' && line[map->x] != 'E' && line[map->x] != 'W' && line[map->x] != '0' && line[map->x] != '1' && line[map->x] != ' ')
				ft_invalid("Invalid character in map\n");
			map->final_map[map->y][map->x] = (line[map->x]);
			if (line[map->x] == ' ')
				map->final_map[map->y][map->x] = '2';
		}
		map->y++;
		free(line);
	}
	close(fd);
}
