
#include "cub3d.h"

void	weapon_init(t_env *env)
{
	int			i;

	i = 0;
	while (i < env->c - 1)
	{
		env->weapon[i] = malloc(sizeof(t_weapon));
		if (!env->weapon[i])
			ft_invalid("Malloc weapon failed\n", env);
		env->weapon[i]->img = mlx_xpm_file_to_image(env->mlx, \
			ft_strjoin(ft_strjoin("texture/item/", ft_itoa(i)), ".xpm"), &env->weapon[i]->width, \
			&env->weapon[i]->height);
		if (!env->weapon[i]->img)
			ft_invalid("weapon loading failed\n", env);
		env->weapon[i]->data = \
			(int *)mlx_get_data_addr(env->weapon[i]->img, \
			&env->weapon[i]->bits_per_pixel, &env->weapon[i]->line_length, \
			&env->weapon[i]->endian);
		if (!env->weapon[i]->data)
			ft_invalid("weapon data loading failed\n", env);
		i++;
	}
}

void	draw_weapon(t_env *env)
{
	int		i;
	int		j;
	int		color;

	i = 0;
	while (i < env->weapon->height)
	{
		j = 0;
		while (j < env->weapon->width)
		{
			color = *(unsigned int *)(env->weapon->data + \
				(i * env->weapon->line_length + j * \
				env->weapon->bits_per_pixel / 8));
			if (color != 0x00000000)
				draw_pixel_to_image(env, \
					WINDOW_WIDTH / 2 - env->weapon->width / 2 + j, \
					WINDOW_HEIGHT - env->weapon->height + i, color);
			j++;
		}
		i++;
	}
}
