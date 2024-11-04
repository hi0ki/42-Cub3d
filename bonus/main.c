/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:46:15 by kadam             #+#    #+#             */
/*   Updated: 2024/11/04 14:01:59 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

static void	player_position(t_data *data, int x, int y)
{
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("WESN", data->map[y][x]))
			{
				if (data->map[y][x] == 'N')
					data->player.angle = 3 * M_PI_2;
				else if (data->map[y][x] == 'E')
					data->player.angle = M_PI;
				else if (data->map[y][x] == 'S')
					data->player.angle = M_PI_2;
				else if (data->map[y][x] == 'W')
					data->player.angle = 0;
				data->player.px = (x * SIZE) + SIZE / 2;
				data->player.py = (y * SIZE) + SIZE / 2;
				break ;
			}
			x++;
		}
		y++;
	}
}
void mouse_hook(void *param)
{
	static int old_x;
	t_data *data;
	int new_y;
	int new_x;

	data = (t_data *)param;
	mlx_set_cursor_mode(data->mlx, 	MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(data->mlx, &new_x, &new_y);
	if (new_x < 0 || new_x > WIDTH || new_y < 0 || new_y > HEIGHT)
	{
		if (new_x < 0)
			new_x = WIDTH;
		if (new_x > WIDTH)
			new_x = 0;
		if (new_y < 0)
			new_y = HEIGHT;
		if (new_y > HEIGHT)
			new_y = 0;
		mlx_set_mouse_pos(data->mlx, new_x, new_y);
	};
	if (new_x - 3 > old_x && new_x != 0 && new_x != WIDTH && new_y != 0 && new_y != HEIGHT)
		data->player.angle += ROTATION_SPEED;
	if (new_x + 3 < old_x && new_x != 0 && new_x != WIDTH && new_y != 0 && new_y != HEIGHT)
		data->player.angle -= ROTATION_SPEED;
	old_x = new_x;
}

int	main(int ac, char **av)
{
	t_data	map_struct;
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
	mlx_set_mouse_pos(map_struct.mlx, WIDTH / 2, HEIGHT / 2);
	mlx_loop_hook(map_struct.mlx, &mouse_hook, &map_struct);
	mlx_loop_hook(map_struct.mlx, &start_drawing, &map_struct);
    mlx_loop_hook(map_struct.mlx, &start_key_hook, &map_struct);
	mlx_loop(map_struct.mlx);
	return (0);
}
