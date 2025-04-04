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

// void	check_map(char *line)
// {
// 	int	i;
// 	int	len;

// 	len = ft_strlen(line);
// 	i = 0;
// 	if
// 	while (line[i])
// 	{

// 	}
// }
