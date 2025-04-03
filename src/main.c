/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:11:40 by kyang             #+#    #+#             */
/*   Updated: 2025/04/03 11:04:56 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	t_env		env;

	(void)argc;
	(void)argv;
	map_init(&map);
	map_delimit(&map, argv[1]);
	map_parsing(&map, argv[1]);
	init_player_dir(&player, &map);
	init_mlx(&env, &map, &player);


	// map.y = 0;
	// while (map.y < map.h_max)
	// {
		// map.x = 0;
		// while (map.x < map.w_max)
		// {
//
			// printf("%c",map.final_map[map.y][map.x]);
			// map.x++;
		// }
		// printf("\n");
		// map.y++;
	// }
	// map.y = 0;
	// while (map.y < map.h_max)
	// {
		// free(map.final_map[map.y]);
		// map.y++;
	// }
	return (0);
}
