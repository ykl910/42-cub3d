/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbellest <tbellest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:11:40 by kyang             #+#    #+#             */
/*   Updated: 2025/04/02 17:35:21 by tbellest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_map	map;
	t_player	player;

	map_init(&map);
	(void)argc;
	map_delimit(&map, argv[1]);
	printf("w_max = %d\n", map.w_max);
	printf("h_max = %d\n", map.h_max);
	printf("map_start = %d\n", map.map_start);
	map_parsing(&map, argv[1]);
	init_player_dir(&player, &map);
	init_player_cam(&player, &map);
	printf("posX = %f\n", player.posX);
	printf("posY = %f\n", player.posY);
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
