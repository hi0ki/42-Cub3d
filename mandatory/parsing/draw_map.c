/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
/*   Updated: 2024/10/18 17:02:43 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int color_pixel(int *arr, int index)
{
    if (index == 0)
        return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | arr[3]);
    else
        return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | 0xFF);
}

void start_drawing(void *ptr)
{
    t_map *map = (t_map *)ptr;

    mlx_delete_image(map->mlx, map->image);
    map->image = mlx_new_image(map->mlx, WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT / 2; y++)
    {
        for (int x = 0; x < WIDTH; x++)
            mlx_put_pixel(map->image, x, y, color_pixel(map->C, 1));
    }
    for (int y = HEIGHT / 2; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
            mlx_put_pixel(map->image, x, y, color_pixel(map->F, 1));
    }
    map->player.angle = fmod(map->player.angle, 2 * M_PI);
    if (map->player.angle < 0)
        map->player.angle += 2 * M_PI;
    start_raycasting(map);
    mlx_image_to_window(map->mlx, map->image, 0, 0);
}