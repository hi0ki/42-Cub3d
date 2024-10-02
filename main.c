/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:46:15 by kadam             #+#    #+#             */
/*   Updated: 2024/09/28 13:06:21 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"



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
    map_struct.player.angle = 0;
    map_struct.player.px = -1;
    map_struct.player.py = -1;
    int x = 0, y = 0;
    while (map_struct.map_array[y])
    {
        x = 0;
        while (map_struct.map_array[y][x])
        {
            if (ft_strchr("WESN", map_struct.map_array[y][x]))
            {
                if (map_struct.map_array[y][x] == 'N')
                    map_struct.player.angle = 3 * M_PI_2;
                else if (map_struct.map_array[y][x] == 'E')
                    map_struct.player.angle = M_PI;
                else if (map_struct.map_array[y][x] == 'S')
                    map_struct.player.angle = M_PI_2;
                else if (map_struct.map_array[y][x] == 'W')
                    map_struct.player.angle = 0;
                map_struct.player.px = x * Size;
                map_struct.player.py = y * Size;
                break;
            }
            x++;
        }
        y++;
    }

    map_struct.mlx = mlx_init(1200, 600, "Cub3D", 0);
    map_struct.image = mlx_new_image(map_struct.mlx, 1200, 600);
    map_struct.player.image_player = mlx_new_image(map_struct.mlx, 1200, 600);
    draw_map(&map_struct);
    mlx_image_to_window(map_struct.mlx, map_struct.image, 100, 70);
    mlx_image_to_window(map_struct.mlx, map_struct.player.image_player, 100, 70);
    mlx_key_hook(map_struct.mlx, &key_hook, &map_struct);
    mlx_loop(map_struct.mlx);
    return (0);
}
