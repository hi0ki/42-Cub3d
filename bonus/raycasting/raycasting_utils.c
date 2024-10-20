/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:57:13 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/20 11:58:56 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int check_pos(t_map *map, double py, double px, double num_pix)
{
    int y;
    int x;

    x = px / SIZE;
    y = (py + num_pix) / SIZE;
    if (map->map_array[y] && map->map_array[y][x] == '1')
        return (-1);
    y = (py - num_pix) / SIZE;
    if (y >= 0 && map->map_array[y][x] == '1')
        return (-1);
    y = py / SIZE;
    x = (px + num_pix) / SIZE;
    if (map->map_array[y][x] && map->map_array[y][x] == '1')
        return (-1);
    x = (px - num_pix) / SIZE;
    if (x >= 0 && map->map_array[y][x] == '1')
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

    ay = y / SIZE;
    ax = x / SIZE;
    if (ay < 0 || ay >= ft_lenarray(map->map_array) ||
        ax >= _strlen(map->map_array[ay]) || ax < 0)
        return (-1);
    if (check_pos(map, y, x, 0.000001) == -1)
        return (-1);
    if (map->map_array[ay][ax] && map->map_array[ay][ax] == '1')
        return (-1);
    return (0);
}

void draw_3d(t_map *map, double line_height, int i, t_rays rays)
{
    double top;
    double bot;
    int tex_y;
    int tex_indexx = tex_index(rays.dis_H, rays.dis_V, rays.rayangle);

    top = (HEIGHT / 2) - (line_height / 2);
    int j = top;
    bot = (HEIGHT / 2) + (line_height / 2);
    if (top < 0)
        top = 0;
    if (bot > HEIGHT)
        bot = HEIGHT;
    while (top < bot)
    {
        tex_y = ((top - j) / line_height) * map->textur[tex_indexx]->height;
        mlx_put_pixel(map->image, i, top, get_color(map, rays, tex_y, tex_indexx));
        top++;
    }
}
