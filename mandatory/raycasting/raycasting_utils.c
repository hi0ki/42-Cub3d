/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:57:13 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/15 19:45:08 by eel-ansa         ###   ########.fr       */
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
    if (y >= 0 && map->map_array[y][x] == '1')
        return (-1);
    y = py / Size;
    x = (px + num_pix) / Size;
    if (map->map_array[y][x] && map->map_array[y][x] == '1')
        return (-1);
    x = (px - num_pix) / Size;
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

    ay = y / Size;
    ax = x / Size;
    if (ay < 0 || ay >= ft_lenarray(map->map_array) ||
        ax >= _strlen(map->map_array[ay]) || ax < 0)
        return (-1);
    if (check_pos(map, y, x, 0.000001) == -1)
        return (-1);
    if (map->map_array[ay][ax] && map->map_array[ay][ax] == '1')
        return (-1);
    return (0);
}

int get_color_pixel(uint8_t *arr)
{
    return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | 0xFF);
}

int get_color(t_map *map, t_dis_H dis_H, t_dis_V dis_V, int tex_y, int texture_index)
{
    int tex_x = 0;
    if (dis_H.inter_type_H == 'H')
        tex_x = ((dis_H.x_H / Size) - floor(dis_H.x_H / Size)) * map->textur[texture_index]->width;
    else if (dis_V.inter_type_V == 'V')
        tex_x = ((dis_V.y_V / Size) - floor(dis_V.y_V / Size)) * map->textur[texture_index]->width;
    if (tex_x < 0 || tex_y < 0 || (uint32_t)tex_x >= map->textur[texture_index]->width || (uint32_t)tex_y >= map->textur[texture_index]->height)
        return (0);
    int index = (tex_y * map->textur[texture_index]->width * map->textur[texture_index]->bytes_per_pixel) + (tex_x * map->textur[texture_index]->bytes_per_pixel);
    return get_color_pixel(&map->textur[texture_index]->pixels[index]);
}

void draw_3d(t_map *map, double line_height, int i, t_dis_H *dis_H, t_dis_V *dis_V, int texture_index)
{
    double top;
    double bot;
    int tex_y;
    top = (HEIGHT / 2) - (line_height / 2);
    bot = (HEIGHT / 2) + (line_height / 2);
    int j = top;
    if (top < 0)
        top = 0;
    if (bot > HEIGHT)
        bot = HEIGHT;
    while (top < bot)
    {
        tex_y = ((top - j) / line_height) * map->textur[texture_index]->height;
        mlx_put_pixel(map->image, i, top, get_color(map, dis_H[i], dis_V[i], tex_y, texture_index));
        top++;
    }
}
