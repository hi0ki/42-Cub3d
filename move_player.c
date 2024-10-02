/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:50:58 by kadam             #+#    #+#             */
/*   Updated: 2024/10/01 17:43:21 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int check_pos(t_map *map, double py, double px, int num_pix)
{
    int y;
    int x;

    x = px / Size;
    y = (py + num_pix) / Size;
    if (map->map_array[y] && map->map_array[y][x] == '1')
        return (-1);
    y = (py - num_pix) / Size;
    if (y > 0 && map->map_array[y][x] == '1')
        return (-1);
    y = py / Size;
    x = (px + num_pix) / Size;
    if (map->map_array[y][x] && map->map_array[y][x] == '1')
        return (-1);
    x = (px - num_pix) / Size;
    if (x > 0 && map->map_array[y][x] == '1')
        return (-1);
    return (0);
}

double count_dis(double xp, double yp, double x, double y)
{
    double dx = x - xp;
    double dy = y - yp;
    return (sqrt(dx * dx + dy * dy));
}

int check_ray(t_map *map, double y, double x)
{
    int ay;
    int ax;

    ay = y / Size;
    ax = x / Size;
    if (ay < 0 || ay >= ft_lenarray(map->map_array) || 
        ax >= _strlen(map->map_array[ay]) || ax < 0)
            return (-1);
    if (check_pos(map, y, x, 1) == -1)
        return (-1);
    if (map->map_array[ay][ax] && map->map_array[ay][ax] == '1')
        return (-1);
    return (0);
}


/*
khasni mochkil dyal sigv li kayw9t on3rf ki kaydar y dyal verticale
*/

double raycasting(t_map *map , double rayangle)
{
    double vdis = 0;
    double hdis = 0;
    double y = 0;
    double x = 0;
    if (rayangle >= M_PI)
    {
        y = floor(map->player.py / Size) * Size - 0.001;
        x = ((y - map->player.py) / tan(rayangle)) + map->player.px;
        while (1)
        {
            if (check_ray(map, y, x) == -1)
                break ;
            y += -Size;
            x += -Size / tan(rayangle);
        }
        hdis = count_dis(map->player.px, map->player.py, x, y);
    }
    else
    {
        y = floor((map->player.py) / Size) * Size + Size;
        x = ((y - map->player.py) / tan(rayangle)) + map->player.px;
        while (1)
        {
            if (check_ray(map, y, x) == -1)
                break ;
            y += Size;
            x += Size / tan(rayangle);
        }
        hdis = count_dis(map->player.px, map->player.py, x, y);
    }
    if (rayangle > M_PI_2 && rayangle <  M_PI_2 * 3)
    {
        x = floor( map->player.px / Size) * Size - 0.001;
        y = map->player.py + (x - map->player.px) * tan(rayangle);
        while (1)
        {
            if (check_ray(map, y, x) == -1)
                break ;
            x -=32;
            y += -Size * tan(rayangle);
        }
        vdis = count_dis(map->player.px, map->player.py, x, y);
    }
    else
    {
        x = floor((map->player.px + Size) / Size) * Size;
        y = map->player.py + (x - map->player.px) * tan(rayangle);
        while (1)
        {
            if (check_ray(map, y, x) == -1)
                break ;
            x += 32;
            y += Size * tan(rayangle);
        }
        vdis = count_dis(map->player.px, map->player.py, x, y);
    }
    if (vdis < hdis && vdis > 0)
        return (vdis);
    else
        return (hdis);
}

void draw_rays(t_map *map)
{
    double fov = 60 * (M_PI / 180);
    double rayangle = map->player.angle - fov / 2;
    double angle = fov / WIDTH;
    double dis = 0;
    int i = 0;
    while (i < WIDTH)
    {
        rayangle = fmod(rayangle, 2 * M_PI);
        if (rayangle < 0)
            rayangle += 2 * M_PI;
        dis = raycasting(map, rayangle);
        draw_line(map->player.image_player, map->player.px, map->player.py, dis, GREEN, rayangle);
        rayangle += angle;
        i++;
    }
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_map *map = (t_map *)param;
    double new_px = map->player.px;
    double new_py = map->player.py;

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
        mlx_delete_image(map->mlx, map->player.image_player);
        map->player.image_player = mlx_new_image(map->mlx, 1200, 600);
        mlx_put_pixel(map->player.image_player, new_px, new_py, RED);
        draw_rays(map);
        mlx_image_to_window(map->mlx, map->player.image_player, 100, 70);
    }
} 
