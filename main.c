/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:46:15 by kadam             #+#    #+#             */
/*   Updated: 2024/10/14 15:13:43 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int main(int ac, char **av)
{
    static t_map map_struct;
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
    map_struct.mlx = NULL;
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
                map_struct.player.px = x * Size + Size / 2;
                map_struct.player.py = y * Size + Size / 2;
                break;
            }
            x++;
        }
        y++;
    }
    map_struct.textur[0] = mlx_load_png(map_struct.NO);
    map_struct.textur[1] = mlx_load_png(map_struct.SO);
    map_struct.textur[2] = mlx_load_png(map_struct.WE);
    map_struct.textur[3] = mlx_load_png(map_struct.EA);
    if (!map_struct.textur[0] || !map_struct.textur[1] || !map_struct.textur[2] || !map_struct.textur[3])
        return (ft_putstrn_fd("Error: Unable to load texture", 2), 1);
    map_struct.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
    mlx_loop_hook(map_struct.mlx, &start_drawing, &map_struct);
    mlx_key_hook(map_struct.mlx, &key_hook, &map_struct);
    mlx_loop(map_struct.mlx);
    return (0);
}
