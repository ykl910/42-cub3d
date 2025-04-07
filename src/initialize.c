/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:55:05 by tbellest          #+#    #+#             */
/*   Updated: 2025/04/04 12:56:10 by tbellest         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keys_init(t_env *env)
{
	env->keys[A] = 0;
	env->keys[W] = 0;
	env->keys[S] = 0;
	env->keys[D] = 0;
	env->keys[LEFT] = 0;
	env->keys[RIGHT] = 0;

}

void	init_mlx(t_env	*env)
{
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		return ;
	env->win = mlx_new_window(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (env->win == NULL)
		return ;
	env->img = mlx_new_image(env->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, \
	&env->line_length, &env->endian);
	if (env->addr == NULL)
		return ;
}

void	init_texture(t_env *env)
{
	int			i;

	i = 0;
	if (access(env->texture_path[i], F_OK) != 0)
	{
		printf("texture path[%d]: %s\n", i, env->texture_path[i]);
		ft_putstr_fd("Erreur: fichier de texture introuvable\n", 2);
		exit(1);
	}
	while (i < 4)
	{
		//printf("texture path[%d]: %s\n", i, env->texture_path[i]);
		env->textures[i] = malloc(sizeof(t_texture));
		if (!env->textures[i])
		{
			ft_putstr_fd("Erreur: allocation mémoire échouée pour la texture\n", 2);
			exit(1); // Ajoutez une fonction pour libérer les ressources
		}
		env->textures[i]->img = mlx_xpm_file_to_image(env->mlx, \
			env->texture_path[i], &env->textures[i]->width, &env->textures[i]->height);
		if (!env->textures[i]->img)
		{
			ft_putstr_fd("Erreur: texture non chargée\n", 2);
			exit(1); // Ajoutez une fonction pour libérer les ressources
		}
		env->textures[i]->data = (int *)mlx_get_data_addr(env->textures[i]->img, \
			&env->textures[i]->bits_per_pixel, &env->textures[i]->line_length, \
			&env->textures[i]->endian);
		if (!env->textures[i]->data)
		{
			ft_putstr_fd("Erreur: données de texture non accessibles\n", 2);
			exit(1); // Ajoutez une fonction pour libérer les ressources
		}
		i++;
	}
}
