/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:50:58 by kadam             #+#    #+#             */
/*   Updated: 2024/10/06 12:50:15 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_map *map = (t_map *)param;
    double new_px = map->player.px;
    double new_py = map->player.py;

    // printf("angle = %f\n", map->player.angle);
    if (keydata.key == MLX_KEY_W && keydata.action)
    {
        new_px += cos(map->player.angle) * MOVE_SPEED;
        new_py += sin(map->player.angle) * MOVE_SPEED;
    }
    else if (keydata.key == MLX_KEY_S && keydata.action)
    {
        new_px -= cos(map->player.angle) * MOVE_SPEED;
        new_py -= sin(map->player.angle) * MOVE_SPEED;
    }
    else if (keydata.key == MLX_KEY_A && keydata.action)
    {
        new_px += sin(map->player.angle) * MOVE_SPEED;
        new_py -= cos(map->player.angle) * MOVE_SPEED;
    }
    else if (keydata.key == MLX_KEY_D && keydata.action)
    {
        new_px -= sin(map->player.angle) * MOVE_SPEED;
        new_py += cos(map->player.angle) * MOVE_SPEED;
    }
    if (keydata.key == MLX_KEY_LEFT && keydata.action)
        map->player.angle -= ROTATION_SPEED;
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action)
        map->player.angle += ROTATION_SPEED;
    else if (keydata.key == MLX_KEY_ESCAPE && keydata.action)
        exit(1);
    map->player.angle = fmod(map->player.angle, 2 * M_PI);
    if (map->player.angle < 0)
        map->player.angle += 2 * M_PI;
    if (check_pos(map, new_py, new_px, 4) == 0)
    {
        map->player.px = new_px;
        map->player.py = new_py;
    }
}
