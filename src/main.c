/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyang <kyang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:11:40 by kyang             #+#    #+#             */
/*   Updated: 2025/04/17 17:00:32 by kyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	t_env		env;

	(void)argc;
	init_env(&env);
	env.map = &map;
	env.player = &player;
	init_map(&map, &env, argv[1]);
	map_delimit(&map, argv[1], &env);
	map_parsing(&env, argv[1]);
	init_player_dir(&player, &map);
	init_mlx(&env);
	init_texture(&env);
	weapon_init(&env);
	mlx_hook(env.win, KeyPress, KeyPressMask, key_press, &env);
	mlx_hook(env.win, KeyRelease, KeyReleaseMask, key_release, &env);
	mlx_hook(env.win, MotionNotify, PointerMotionMask, mouse_move, &env);
	mlx_loop_hook(env.mlx, render_loop, &env);
	mlx_hook(env.win, 17, 0, handle_destroy, &env);
	mlx_loop(env.mlx);
	return (0);
}
