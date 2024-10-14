/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:02 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/14 13:33:48 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double distance_hrz(t_map *map, t_dis_H *dis_H, double angle)
{
    double hdis;
    double ya;

    if (angle >= M_PI)
    {
        dis_H->y_H = floor(map->player.py / Size) * Size - 0.000001;
        ya = -Size;
    }
    else
    {
        dis_H->y_H = floor((map->player.py) / Size) * Size + Size;
        ya = Size;
    }
    dis_H->x_H = ((dis_H->y_H - map->player.py) / tan(angle)) + map->player.px;
    while (1)
    {
        if (check_ray(map, dis_H->y_H, dis_H->x_H) == -1)
            break;
        dis_H->y_H += ya;
        dis_H->x_H += ya / tan(angle);
    }
    hdis = cal_dis(map->player.px, map->player.py, dis_H->x_H, dis_H->y_H);
    return (hdis);
}

double distance_vrt(t_map *map, t_dis_V *dis_V, double angle)
{
    double vdis;
    double xa;

    if (angle > M_PI_2 && angle < M_PI_2 * 3)
    {
        dis_V->x_V = floor(map->player.px / Size) * Size - 0.000001;
        xa = -Size;
    }
    else
    {
        dis_V->x_V = floor(map->player.px / Size) * Size + Size;
        xa = Size;
    }
    dis_V->y_V = map->player.py + (dis_V->x_V - map->player.px) * tan(angle);
    while (1)
    {
        if (check_ray(map, dis_V->y_V, dis_V->x_V) == -1)
            break;
        dis_V->x_V += xa;
        dis_V->y_V += xa * tan(angle);
    }
    vdis = cal_dis(map->player.px, map->player.py, dis_V->x_V, dis_V->y_V);
    return (vdis);
}

double cal_distance(t_map *map, t_dis_H *dis_H, t_dis_V *dis_V, double rayangle)
{
    double vdis = 0;
    double hdis = 0;

    hdis = distance_hrz(map, dis_H, rayangle);
    vdis = distance_vrt(map, dis_V, rayangle);
    if (vdis < hdis && vdis > 0)
    {
        dis_H->inter_type_H = 'N';
        dis_V->inter_type_V = 'V';
        return (vdis);
    }
    else
    {
        dis_V->inter_type_V = 'N';
        dis_H->inter_type_H = 'H';
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
    t_dis_H *dis_H = malloc(sizeof(t_dis_H) * WIDTH);
    t_dis_V *dis_V = malloc(sizeof(t_dis_V) * WIDTH);
    
    while (i < WIDTH)
    {
        rayangle = fmod(rayangle, 2 * M_PI);
        if (rayangle < 0)
            rayangle += 2 * M_PI;
        dis = cal_distance(map, &dis_H[i], &dis_V[i], rayangle) * cos(map->player.angle - rayangle);
        line_height = (Size / dis) * (WIDTH / 2) / tan(fov / 2);
        int tex_index = 0;
        // Vertical
        if (dis_V[i].inter_type_V == 'V')
        {
            if (rayangle > M_PI_2 && rayangle < 3 * M_PI_2) //south
                tex_index = 2;
            else //west
                tex_index = 3;
        }
        // Horizontal
        else if (dis_H[i].inter_type_H == 'H')
        {
            if (rayangle > M_PI && rayangle < 2 * M_PI) //south
                tex_index = 1;
            else  //north
                tex_index = 0;
        }
        draw_3d(map, line_height, i, dis_H, dis_V, tex_index);
        rayangle += angle;
        i++;
    }
    free(dis_H);
    free(dis_V);
}
