/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:02 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/08 19:21:42 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double distance_hrz(t_map *map, t_dis *dis_arr, double angle)
{
    double hdis;
    double ya;

    if (angle >= M_PI)
    {
        dis_arr->y = floor(map->player.py / Size) * Size - 0.001;
        ya = -Size;
    }
    else
    {
        dis_arr->y = floor((map->player.py) / Size) * Size + Size;
        ya = Size;
    }
    dis_arr->x = ((dis_arr->y - map->player.py) / tan(angle)) + map->player.px;
    while (1)
    {
        if (check_ray(map, dis_arr->y, dis_arr->x) == -1)
            break ;
        dis_arr->y += ya;
        dis_arr->x += ya / tan(angle);
    }
    hdis = cal_dis(map->player.px, map->player.py, dis_arr->x, dis_arr->y);
    return (hdis);
}

double distance_vrt(t_map *map, t_dis *dis_arr, double angle)
{
    double vdis;
    double xa;

    if (angle > M_PI_2 && angle <  M_PI_2 * 3)
    {
        dis_arr->x = floor(map->player.px / Size) * Size - 0.001;
        xa = -Size;
    }
    else
    {
        dis_arr->x = floor(map->player.px / Size) * Size + Size;
        xa = Size;
    }
    dis_arr->y = map->player.py + (dis_arr->x - map->player.px) * tan(angle);
    while (1)
    {
        if (check_ray(map, dis_arr->y, dis_arr->x) == -1)
            break ;
        dis_arr->x += xa;
        dis_arr->y += xa * tan(angle);
    }
    vdis = cal_dis(map->player.px, map->player.py, dis_arr->x, dis_arr->y);
    return (vdis);
}
double cal_distance(t_map *map , t_dis *dis_arr, double rayangle)
{
    double vdis = 0;
    double hdis = 0;
    
    hdis = distance_hrz(map, dis_arr, rayangle);
    vdis = distance_vrt(map, dis_arr, rayangle);
    if (vdis < hdis && vdis > 0)
    {
        dis_arr->inter_type = 'V';   
        return (vdis);
    }
    else
    {
        dis_arr->inter_type = 'H';
        return (hdis);
    }
}

void start_raycasting(t_map *map)
{
    double fov = 60 * (M_PI / 180);
    double rayangle = map->player.angle - fov / 2;
    double angle = fov / WIDTH;
    double dis = 0;
    double line_height = 0;
    int i = 0;
    t_dis *dis_arr = malloc(sizeof(t_dis) * WIDTH);
    while (i < WIDTH)
    {
        rayangle = fmod(rayangle, 2 * M_PI);
        if (rayangle < 0)
            rayangle += 2 * M_PI;
        dis = cal_distance(map, &dis_arr[i],rayangle) * cos(map->player.angle - rayangle);
        line_height = (Size / dis) * (WIDTH / 2) / tan(fov / 2);
        draw_3d(map, dis, line_height, i, dis_arr);
        rayangle += angle;
        i++;
    }
    free(dis_arr);
}
