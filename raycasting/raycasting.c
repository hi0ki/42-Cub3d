/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:02 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/05 11:16:07 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double distance_hrz(t_map *map, double x, double y , double angle)
{
    double hdis;
    double ya;

    if (angle >= M_PI)
    {
        y = floor(map->player.py / Size) * Size - 0.001;
        ya = -Size;
    }
    else
    {
        y = floor((map->player.py) / Size) * Size + Size;
        ya = Size;
    }
    x = ((y - map->player.py) / tan(angle)) + map->player.px;
    while (1)
    {
        if (check_ray(map, y, x) == -1)
            break ;
        y += ya;
        x += ya / tan(angle);
    }
    hdis = cal_dis(map->player.px, map->player.py, x, y);
    return (hdis);
}

double distance_vrt(t_map *map, double x, double y , double angle)
{
    double vdis;
    double xa;

    if (angle > M_PI_2 && angle <  M_PI_2 * 3)
    {
        x = floor(map->player.px / Size) * Size - 0.001;
        xa = -Size;
    }
    else
    {
        x = floor(map->player.px / Size) * Size + Size;
        xa = Size;
    }
    y = map->player.py + (x - map->player.px) * tan(angle);
    while (1)
    {
        if (check_ray(map, y, x) == -1)
            break ;
        x += xa;
        y += xa * tan(angle);
    }
    vdis = cal_dis(map->player.px, map->player.py, x, y);
    return (vdis);
}
double cal_distance(t_map *map , double rayangle)
{
    double vdis = 0;
    double hdis = 0;
    double y = 0;
    double x = 0;
    
    hdis = distance_hrz(map, x, y, rayangle);
    vdis = distance_vrt(map, x, y, rayangle);
    if (vdis < hdis && vdis > 0)
        return (vdis);
    else
        return (hdis);
}

void start_raycasting(t_map *map)
{
    double fov = 60 * (M_PI / 180);
    double rayangle = map->player.angle - fov / 2;
    double angle = fov / WIDTH;
    double dis = 0;
    double line_height = 0;
    int i = 0;
    while (i < WIDTH)
    {
        rayangle = fmod(rayangle, 2 * M_PI);
        if (rayangle < 0)
            rayangle += 2 * M_PI;
        dis = cal_distance(map, rayangle);
        line_height = (32 / dis) * (WIDTH / 2) / tan(fov / 2);
        draw_line(map->player.image_player, map->player.px, map->player.py, dis, GREEN, rayangle);
        draw_3d(map, dis, line_height, i);
        rayangle += angle;
        i++;
    }
}
