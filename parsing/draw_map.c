/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
/*   Updated: 2024/10/14 15:26:18 by eel-ansa         ###   ########.fr       */
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

void draw_cros(t_map *map)
{
    double x = WIDTH / 2;
    double y = HEIGHT / 2;
    draw_line(map->image, x - 3, y, 6, GREEN, M_PI); // lift
    draw_line(map->image, x, y - 3, 6, GREEN, M_PI_2 * 3); // top
    draw_line(map->image, x, y + 3, 6, GREEN, M_PI_2); // bot
    draw_line(map->image, x + 3, y, 6, GREEN, 0); // right
}

void start_drawing(void *ptr)
{
    t_map *map = (t_map *)ptr;

    mlx_delete_image(map->mlx, map->image);
    map->image = mlx_new_image(map->mlx, WIDTH, HEIGHT);
    // mlx_put_pixel(map->image, map->player.px, map->player.py, RED);
    map->player.angle = fmod(map->player.angle, 2 * M_PI);
    if (map->player.angle < 0)
        map->player.angle += 2 * M_PI;
    start_raycasting(map);
    draw_cros(map);
    // draw_background(map);
    // draw_minimap(map);
    mlx_image_to_window(map->mlx, map->image, 0, 0);
}