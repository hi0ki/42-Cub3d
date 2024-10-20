/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:46:15 by kadam             #+#    #+#             */
/*   Updated: 2024/10/20 12:42:31 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	player_position(t_map *map, int x, int y)
{
	while (map->map_array[y])
	{
		x = 0;
		while (map->map_array[y][x])
		{
			if (ft_strchr("WESN", map->map_array[y][x]))
			{
				if (map->map_array[y][x] == 'N')
					map->player.angle = 3 * M_PI_2;
				else if (map->map_array[y][x] == 'E')
					map->player.angle = M_PI;
				else if (map->map_array[y][x] == 'S')
					map->player.angle = M_PI_2;
				else if (map->map_array[y][x] == 'W')
					map->player.angle = 0;
				map->player.px = (x * SIZE) + SIZE / 2;
				map->player.py = (y * SIZE) + SIZE / 2;
				break ;
			}
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_map	map_struct;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstrn_fd("Error: Unable to open file", 2), 1);
	if (check_all(ac, av, &map_struct, fd))
		return (close(fd), 1);
	close(fd);
	check_map(&map_struct);
	player_position(&map_struct, 0, 0);
	map_struct.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	mlx_loop_hook(map_struct.mlx, &start_drawing, &map_struct);
    mlx_loop_hook(map_struct.mlx, &start_key_hook, &map_struct);
	mlx_loop(map_struct.mlx);
	return (0);
}
