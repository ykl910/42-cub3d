/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:11:40 by kyang             #+#    #+#             */
/*   Updated: 2025/04/04 16:17:30 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	t_env		env;

	(void)argc;

	keys_init(&env);
	map_init(&map);
	map_delimit(&map, argv[1]);
	map_parsing(&map, argv[1]);
	print_map(&map);
	init_player_dir(&player, &map);
	env.player = &player;
	env.map = &map;
	init_mlx(&env);
	mlx_hook(env.win, KeyPress, KeyPressMask, key_press, &env);
	mlx_hook(env.win, KeyRelease, KeyReleaseMask, key_release, &env);
	mlx_loop_hook(env.mlx, render_loop, &env);
	mlx_hook(env.win, 17, 0, handle_destroy, &env);
	mlx_loop(env.mlx);
	return (0);
}


