/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
/*   Updated: 2024/10/01 15:16:40 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void draw_square(void *image, int x, int y, int size, int color)
{
    int i = 0, j = 0;
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

void draw_border(void *image, int x, int y, int size, int color)
{
    int i = 0, j = 0;
    while (i < size)
    {
        mlx_put_pixel(image, x + i, y, color);
        mlx_put_pixel(image, x + i, y + size - 1, color);
        i++;
    }
    while (j < size)
    {
        mlx_put_pixel(image, x, y + j, color);
        mlx_put_pixel(image, x + size - 1, y + j, color);
        j++;
    }
}

void draw_line(void *image, int x, int y, double size, int color, double angle)
{
    int y1 = 0, x1 = 0;
    
    for (double i = 0; i < size; i++)
    {
        y1 = y + i * sin(angle);
        x1 = x + i * cos(angle);
        if (y1 >= 0 && y1 < HEIGHT && x1 >= 0 && x1 < WIDTH)
            mlx_put_pixel(image, x1, y1, color);
    }
}

void draw_player(void *image, int x, int y, int size, int color)
{
    int i = 0, j = 0;
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
    i = 0;
    j = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_put_pixel(image, x - i, y + j, color);
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
                draw_square(map->image, x * Size, y * Size, Size, 0xFFFFFFFF);
            x++;
        }
        y++;
    }
    x = 0;
    y = 0;
    while (map->map_array[y])
    {
        x = 0;
        while (map->map_array[y][x])
        {
            if (map->map_array[y][x] == '1')
                draw_square(map->image, x * Size, y * Size, Size, 0x000000FF);
            else if (ft_strchr("WESN", map->map_array[y][x]))
            {
                mlx_put_pixel(map->player.image_player, x * Size, y * Size, RED);
                draw_line(map->player.image_player, x * Size, y * Size, 10, 0xFF0000FF, map->player.angle);
            }
            x++;
        }
        y++;
    }
}