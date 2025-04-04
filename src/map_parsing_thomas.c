#include "cub3d.h"

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

void	check_map_wall(char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	printf("line = %s\n", line);
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	printf("i = %d, line[i] = %c \n", i, line[i]);
	if (line[i] != '1')
	{
		free(line);
		ft_invalid("map invalid - no wall\n");
	}
	while (line[len - 2] == ' ' && len > 1)
		len--;
	if (line[len - 2] != '1')
	{
		free(line);
		ft_invalid("map invalid - no wall\n");
	}
}
