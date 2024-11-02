/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:02 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/02 14:02:21 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int h_open_door(t_data *data, t_dis_H *dis_H)
{
    int xa;
    int ya;

    xa = dis_H->x_h / SIZE;
    ya = dis_H->y_h / SIZE;
    if (ya < 0 || ya >= ft_lenarray(data->map) ||
    xa >= _strlen(data->map[ya]) || xa < 0)
        return (0);
    if (data->map[ya][xa] && data->map[ya][xa] == 'O' && dis_H->open_door == false)
    {
        dis_H->x_o = xa;
        dis_H->y_o = ya;
        dis_H->open_door = true;
        printf("dkhlllll\n");
    }
    return (0);
}
int v_open_door(t_data *data, t_dis_V *dis_V)
{
    int xa;
    int ya;

    xa = dis_V->x_v / SIZE;
    ya = dis_V->y_v / SIZE;
    if (ya < 0 || ya >= ft_lenarray(data->map) ||
    xa >= _strlen(data->map[ya]) || xa < 0)
        return (0);
    if (data->map[ya][xa] && data->map[ya][xa] == 'O' && dis_V->open_door == false)
    {
        dis_V->x_o = xa;
        dis_V->y_o = ya;
        dis_V->open_door = true;
        printf("dkhlllllzzzzz\n");
    }
    return (0);
}

double distance_hrz(t_data *data, t_dis_H *dis_H, double angle)
{
    double hdis;
    double ya;

    if (angle >= M_PI)
    {
        dis_H->y_h = floor(data->player.py / SIZE) * SIZE - 0.000001;
        ya = -SIZE;
    }
    else
    {
        dis_H->y_h = floor((data->player.py) / SIZE) * SIZE + SIZE;
        ya = SIZE;
    }
    dis_H->x_h = ((dis_H->y_h - data->player.py) / tan(angle)) + data->player.px;
    while (1)
    {
        if (!h_open_door(data, dis_H) && check_ray(data, dis_H->y_h, dis_H->x_h) == -1)
            break;
        dis_H->y_h += ya;
        dis_H->x_h += ya / tan(angle);
    }
    hdis = cal_dis(data->player.px, data->player.py, dis_H->x_h, dis_H->y_h);
    return (hdis);
}

double distance_vrt(t_data *data, t_dis_V *dis_V, double angle)
{
    double vdis;
    double xa;

    if (angle > M_PI_2 && angle < M_PI_2 * 3)
    {
        dis_V->x_v = floor(data->player.px / SIZE) * SIZE - 0.000001;
        xa = -SIZE;
    }
    else
    {
        dis_V->x_v = floor(data->player.px / SIZE) * SIZE + SIZE;
        xa = SIZE;
    }
    dis_V->y_v = data->player.py + (dis_V->x_v - data->player.px) * tan(angle);
    while (1)
    {
        if (!v_open_door(data, dis_V) && check_ray(data, dis_V->y_v, dis_V->x_v) == -1)
            break;
        dis_V->x_v += xa;
        dis_V->y_v += xa * tan(angle);
    }
    vdis = cal_dis(data->player.px, data->player.py, dis_V->x_v, dis_V->y_v);
    return (vdis);
}

double cal_distance(t_data *data, t_dis_H *dis_H, t_dis_V *dis_V, double rayangle)
{
    double vdis = 0;
    double hdis = 0;

    hdis = distance_hrz(data, dis_H, rayangle);
    vdis = distance_vrt(data, dis_V, rayangle);
    if (vdis < hdis && vdis > 0)
    {
        dis_H->inter_type_h = 'N';
        dis_V->inter_type_v = 'V';
        if (is_door(data->map, dis_V->y_v, dis_V->x_v))
            dis_V->is_door = true;
        else
            dis_V->is_door  = false;
        return (vdis);
    }
    else
    {
        dis_V->inter_type_v = 'N';
        dis_H->inter_type_h = 'H';
        if (is_door(data->map, dis_H->y_h, dis_H->x_h))
            dis_H->is_door  = true;
        else
            dis_H->is_door  = false;
        return (hdis);
    }
}

void start_raycasting(t_data *data)
{
    double fov = 60 * (M_PI / 180);
    double rayangle = data->player.angle - fov / 2;
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
        dis = cal_distance(data, &rays[i].dis_H, &rays[i].dis_V, rayangle);
        dis = dis * cos(data->player.angle - rayangle);
        line_height = (SIZE / dis) * (WIDTH / 2) / tan(fov / 2);
        rays[i].rayangle = rayangle;
        draw_3d(data, line_height, i, rays[i]);
        rayangle += angle;
        i++;
    }
    free(rays);
}
