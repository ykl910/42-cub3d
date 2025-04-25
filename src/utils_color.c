/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:34:38 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/25 12:11:24 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color(char *code, t_env *env, char **temp)
{
	int	i;

	i = 0;
	while (code[i])
	{
		if (ft_isalpha(code[i]))
		{
			if (temp)
				free_char_arr(temp);
			ft_invalid("Invalid color value\n", env, NULL);
		}
		i++;
	}
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
	check_color(temp[0], env, temp);
	check_color(temp[1], env, temp);
	check_color(temp[2], env, temp);
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	free_char_arr(temp);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_invalid("Invalid color value\n", env, NULL);
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}
