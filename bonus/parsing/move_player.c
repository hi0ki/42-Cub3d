/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:50:58 by kadam             #+#    #+#             */
/*   Updated: 2024/10/19 19:31:52 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
    t_map *map = (t_map *)param;
    // (void)button;
    // (void)action;
    (void)mods;
    // (void)map;
    if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
    {
        if(map->index == 0 || map->index == 2)
            map->index = 1;
    }
    if (mods  )
    exit(1);
}

void key_hook(t_map *map)
{
    double new_px = map->player.px;
    double new_py = map->player.py;
    if (mlx_is_key_down(map->mlx, MLX_KEY_W))
    {
        new_px += cos(map->player.angle) * MOVE_SPEED;
        new_py += sin(map->player.angle) * MOVE_SPEED;
    }
    if (mlx_is_key_down(map->mlx, MLX_KEY_S))
    {
        new_px -= cos(map->player.angle) * MOVE_SPEED;
        new_py -= sin(map->player.angle) * MOVE_SPEED;
    }
    if (mlx_is_key_down(map->mlx, MLX_KEY_A))
    {
        new_px += sin(map->player.angle) * MOVE_SPEED;
        new_py -= cos(map->player.angle) * MOVE_SPEED;
    }
    if (mlx_is_key_down(map->mlx, MLX_KEY_D))
    {
        new_px -= sin(map->player.angle) * MOVE_SPEED;
        new_py += cos(map->player.angle) * MOVE_SPEED;
    }
    if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
        map->player.angle -= ROTATION_SPEED;
    else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
        map->player.angle += ROTATION_SPEED;
    if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
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

void start_key_hook(void *param)
{
    t_map *map = (t_map *)param;
    key_hook(map);
    // mlx_mouse_hook(map->mlx, &mouse_hook, map);
}
