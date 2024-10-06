/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:57:13 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/06 12:34:10 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int check_pos(t_map *map, double py, double px, double num_pix)
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

double cal_dis(double xp, double yp, double x, double y)
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
    if (check_pos(map, y, x, 0.001) == -1)
        return (-1);
    if (map->map_array[ay][ax] && map->map_array[ay][ax] == '1')
        return (-1);
    return (0);
}

void draw_3d(t_map *map, double dis, double line_height, int i)
{
    double top;
    double bot;

    (void)dis;
    top = (HEIGHT / 2) - (line_height / 2);
    bot = (HEIGHT / 2) + (line_height / 2);
    if (top < 0)
        top = 0;
    if (bot > HEIGHT)
        bot = HEIGHT;
    while (top < bot)
    {
        mlx_put_pixel(map->image, i, top, 0x80808080);
        top++;
    }
}