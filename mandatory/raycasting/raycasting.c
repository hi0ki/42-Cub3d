/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:02 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/31 12:49:09 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double distance_hrz(t_data *data, t_dis_H *dis_H, double angle)
{
    double hdis;
    double ya;

    if (angle >= M_PI)
    {
        dis_H->y_h = floor(dataplayer.py / SIZE) * SIZE - 0.000001;
        ya = -SIZE;
    }
    else
    {
        dis_H->y_h = floor((dataplayer.py) / SIZE) * SIZE + SIZE;
        ya = SIZE;
    }
    dis_H->x_h = ((dis_H->y_h - dataplayer.py) / tan(angle)) + dataplayer.px;
    while (1)
    {
        if (check_ray(map, dis_H->y_h, dis_H->x_h) == -1)
            break;
        dis_H->y_h += ya;
        dis_H->x_h += ya / tan(angle);
    }
    hdis = cal_dis(dataplayer.px, dataplayer.py, dis_H->x_h, dis_H->y_h);
    return (hdis);
}

double distance_vrt(t_data *data, t_dis_V *dis_V, double angle)
{
    double vdis;
    double xa;

    if (angle > M_PI_2 && angle < M_PI_2 * 3)
    {
        dis_V->x_v = floor(dataplayer.px / SIZE) * SIZE - 0.000001;
        xa = -SIZE;
    }
    else
    {
        dis_V->x_v = floor(dataplayer.px / SIZE) * SIZE + SIZE;
        xa = SIZE;
    }
    dis_V->y_v = dataplayer.py + (dis_V->x_v - dataplayer.px) * tan(angle);
    while (1)
    {
        if (check_ray(map, dis_V->y_v, dis_V->x_v) == -1)
            break;
        dis_V->x_v += xa;
        dis_V->y_v += xa * tan(angle);
    }
    vdis = cal_dis(dataplayer.px, dataplayer.py, dis_V->x_v, dis_V->y_v);
    return (vdis);
}

double cal_distance(t_data *data, t_dis_H *dis_H, t_dis_V *dis_V, double rayangle)
{
    double vdis = 0;
    double hdis = 0;

    hdis = distance_hrz(map, dis_H, rayangle);
    vdis = distance_vrt(map, dis_V, rayangle);
    if (vdis < hdis && vdis > 0)
    {
        dis_H->inter_type_h = 'N';
        dis_V->inter_type_v = 'V';
        return (vdis);
    }
    else
    {
        dis_V->inter_type_v = 'N';
        dis_H->inter_type_h = 'H';
        return (hdis);
    }
}

void start_raycasting(t_data *data)
{
    double fov = 60 * (M_PI / 180);
    double rayangle = dataplayer.angle - fov / 2;
    double angle = fov / WIDTH;
    double dis = 0;
    double line_height = 0;
    int i = 0;
    t_rays *rays = malloc(sizeof(t_rays) * WIDTH);

    while (i < WIDTH)
    {
        rayangle = fmod(rayangle, 2 * M_PI);
        if (rayangle < 0)
            rayangle += 2 * M_PI;
        dis = cal_distance(map, &rays[i].dis_H, &rays[i].dis_V, rayangle);
        dis = dis * cos(dataplayer.angle - rayangle);
        line_height = (SIZE / dis) * (WIDTH / 2) / tan(fov / 2);
        rays[i].rayangle = rayangle;
        draw_3d(map, line_height, i, rays[i]);
        rayangle += angle;
        i++;
    }
    free(rays);
}
