/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:46:15 by kadam             #+#    #+#             */
/*   Updated: 2024/09/06 20:38:02 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void draw_square(void *image, int x, int y, int size, int color)
{
	int i = 0;
	int j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void draw_map(t_map *map)
{
	int x = 0, y = 0;
	while (map->map_array[y])
	{
		x = 0;
		while (map->map_array[y][x])
		{
			if (ft_strchr("WESN10", map->map_array[y][x]))
				draw_square(map->image, x * 32, y * 32, 32, 0xD3D3D3);
			x++;
		}
		y++;
	}
	x = 0, y = 0;
	while (map->map_array[y])
	{
		x = 0;
		while (map->map_array[y][x])
		{
			if (map->map_array[y][x] == '1')
				draw_square(map->image, x * 32, y * 32, 32, 0xFFFFFF);
			else if (ft_strchr("WESN", map->map_array[y][x]))
				draw_square(map->image, x * 32 + 8, y * 32 + 8, 16, 0xFF0000FF);
			x++;
		}
		y++;
	}
}

void move_player_and_draw(t_map *map, int p_x, int p_y, char c, int x)
{
	if (map->map_array[p_y][p_x] != '1')
	{
		map->map_array[map->player.y][map->player.x] = '0';
		draw_square(map->image, map->player.x * 32, map->player.y * 32, 32, 0xD3D3D3);
		if (x == 1)
			map->player.y--;
		else if (x == 2)
			map->player.y++;
		else if (x == 3)
			map->player.x--;
		else if (x == 4)
			map->player.x++;
		map->map_array[map->player.y][map->player.x] = c;
		draw_square(map->image, map->player.x * 32 + 8, map->player.y * 32 + 8, 16, 0xFF0000FF);
	}
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_map *map = (t_map *)param;
	if (keydata.key == MLX_KEY_W && keydata.action)
		move_player_and_draw(map, map->player.x, map->player.y - 1, 'N', 1);
	else if (keydata.key == MLX_KEY_S && keydata.action)
		move_player_and_draw(map, map->player.x, map->player.y + 1, 'N', 2);
	else if (keydata.key == MLX_KEY_A && keydata.action)
		move_player_and_draw(map, map->player.x - 1, map->player.y, 'N', 3);
	else if (keydata.key == MLX_KEY_D && keydata.action)
		move_player_and_draw(map, map->player.x + 1, map->player.y, 'N', 4);
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);
}

int main(int ac, char **av)
{
	t_map map_struct;
	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstrn_fd("Error: Unable to open file", 2), 1);
	if (check_all(ac, av, &map_struct, fd))
		return (close(fd), 1);
	close(fd);
	check_map(&map_struct);
	map_struct.player.x = -1;
	map_struct.player.y = -1;
	int x = 0, y = 0;
	while (map_struct.map_array[y])
	{
		x = 0;
		while (map_struct.map_array[y][x])
		{
			if (ft_strchr("WESN", map_struct.map_array[y][x]))
			{
				if (map_struct.map_array[y][x] == 'N')
					map_struct.player_dir = 0;
				else if (map_struct.map_array[y][x] == 'E')
					map_struct.player_dir = 1;
				else if (map_struct.map_array[y][x] == 'S')
					map_struct.player_dir = 2;
				else if (map_struct.map_array[y][x] == 'W')
					map_struct.player_dir = 3;
				map_struct.player.x = x;
				map_struct.player.y = y;
				break;
			}
			x++;
		}
		y++;
	}
	map_struct.mlx = mlx_init(1920, 1080, "Cub3D", true);
	map_struct.image = mlx_new_image(map_struct.mlx, 1920, 1080);
	draw_map(&map_struct);
	mlx_image_to_window(map_struct.mlx, map_struct.image, 360, 180);
	mlx_key_hook(map_struct.mlx, &key_hook, &map_struct);
	mlx_loop(map_struct.mlx);
	return (0);
}
