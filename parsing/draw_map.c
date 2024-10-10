/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
/*   Updated: 2024/10/08 13:47:40 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void draw_minimap(t_map *map)
{
    if (map->player.image_player)
    {
        mlx_delete_image(map->mlx, map->player.image_player);
    }
    map->player.image_player = mlx_new_image(map->mlx, 100, 100);
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
    x = 0, y = 0;
    mlx_image_to_window(map->mlx, map->player.image_player, 0, 0);
}

static int color_pixel(int *arr)
{
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
            mlx_put_pixel(map->image, x, y, color_pixel(map->C));
    }
    for (int y = HEIGHT / 2; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
            mlx_put_pixel(map->image, x, y, color_pixel(map->F));
    }
    map->player.angle = fmod(map->player.angle, 2 * M_PI);
    if (map->player.angle < 0)
        map->player.angle += 2 * M_PI;
    start_raycasting(map);
    mlx_image_to_window(map->mlx, map->image, 0, 0);
    // draw_minimap(map);
}