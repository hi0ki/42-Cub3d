/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:50:58 by kadam             #+#    #+#             */
/*   Updated: 2024/09/08 17:51:36 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_map *map = (t_map *)param;
    float move_speed = MOVE_SPEED;
    float new_px = map->player.px;
    float new_py = map->player.py;

    if (keydata.key == MLX_KEY_W && keydata.action)
    {
        new_px += cos(map->player.angle) * move_speed;
        new_py += sin(map->player.angle) * move_speed;
    }
    else if (keydata.key == MLX_KEY_S && keydata.action)
    {
        new_px -= cos(map->player.angle) * move_speed;
        new_py -= sin(map->player.angle) * move_speed;
    }
    else if (keydata.key == MLX_KEY_A && keydata.action)
    {
        new_px += sin(map->player.angle) * move_speed;
        new_py -= cos(map->player.angle) * move_speed;
    }
    else if (keydata.key == MLX_KEY_D && keydata.action)
    {
        new_px -= sin(map->player.angle) * move_speed;
        new_py += cos(map->player.angle) * move_speed;
    }
    else if (keydata.key == MLX_KEY_LEFT && keydata.action)
        map->player.angle -= ROTATION_SPEED;
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action)
        map->player.angle += ROTATION_SPEED;
    else if (keydata.key == MLX_KEY_ESCAPE && keydata.action)
        exit(1);
    int map_x = new_px / Size;
    int map_y = new_py / Size;
    if (map->map_array[map_y][map_x] != '1')
    {
        mlx_delete_image(map->mlx, map->player.image_player);
        map->player.image_player = mlx_new_image(map->mlx, 1920, 1080);
        map->player.px = new_px;
        map->player.py = new_py;
        mlx_put_pixel(map->player.image_player, map->player.px, map->player.py, 0xFF0000FF);
        draw_line(map->player.image_player, map->player.px, map->player.py, 16, 0xFF0000FF, map->player.angle);
        mlx_image_to_window(map->mlx, map->player.image_player, 340, 240);
    }
}
