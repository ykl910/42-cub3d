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
