/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:02 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/11 17:15:52 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	distance_hrz(t_data *data, t_dis_h *dis_h, double angle, double ya)
{
	double	hdis;

	if (angle >= M_PI)
	{
		dis_h->y_h = floor(data->player.py / SIZE) * SIZE - 0.000001;
		ya = -SIZE;
	}
	else
	{
		dis_h->y_h = floor((data->player.py) / SIZE) * SIZE + SIZE;
		ya = SIZE;
	}
	dis_h->x_h = ((dis_h->y_h - data->player.py) / tan(angle))
		+ data->player.px;
	while (1)
	{
		if (angle == data->player.angle)
			h_close_d(data, dis_h);
		if (check_ray(data, dis_h->y_h, dis_h->x_h) == -1)
			break ;
		dis_h->y_h += ya;
		dis_h->x_h += ya / tan(angle);
	}
	hdis = cal_dis(data->player.px, data->player.py, dis_h->x_h, dis_h->y_h);
	return (hdis);
}

double	distance_vrt(t_data *data, t_dis_v *dis_v, double angle)
{
	double	vdis;
	double	xa;

	if (angle > M_PI_2 && angle < M_PI_2 * 3)
	{
		dis_v->x_v = floor(data->player.px / SIZE) * SIZE - 0.000001;
		xa = -SIZE;
	}
	else
	{
		dis_v->x_v = floor(data->player.px / SIZE) * SIZE + SIZE;
		xa = SIZE;
	}
	dis_v->y_v = data->player.py + (dis_v->x_v - data->player.px) * tan(angle);
	while (1)
	{
		if (angle == data->player.angle)
			v_close_d(data, dis_v);
		if (check_ray(data, dis_v->y_v, dis_v->x_v) == -1)
			break ;
		dis_v->x_v += xa;
		dis_v->y_v += xa * tan(angle);
	}
	vdis = cal_dis(data->player.px, data->player.py, dis_v->x_v, dis_v->y_v);
	return (vdis);
}

double	cal_distance(t_data *data, t_dis_h *dis_h, t_dis_v *dis_v,
		double rayangle)
{
	double	vdis;
	double	hdis;

	vdis = 0;
	hdis = 0;
	hdis = distance_hrz(data, dis_h, rayangle, 0);
	vdis = distance_vrt(data, dis_v, rayangle);
	if (vdis < hdis && vdis > 0)
	{
		dis_v->inter_type_v = 'V';
		dis_v->dis = vdis;
		if (open_d(data->map, dis_v->y_v, dis_v->x_v))
			dis_v->open_d = true;
		return (vdis);
	}
	else
	{
		dis_h->inter_type_h = 'H';
		dis_h->dis = hdis;
		if (open_d(data->map, dis_h->y_h, dis_h->x_h))
			dis_h->open_d = true;
		return (hdis);
	}
}

void	start_raycasting(t_data *data, int i, double dis)
{
	double	rayangle;
	double	angle;
	double	line_height;
	t_rays	*rays;

	rayangle = data->player.angle - FOV / 2;
	angle = FOV / WIDTH;
	line_height = 0;
	rays = malloc(sizeof(t_rays) * WIDTH);
	while (i < WIDTH)
	{
		rayangle = ft_normalize(rayangle);
		rays[i].dis_v.open_d = false;
		rays[i].dis_h.open_d = false;
		rays[i].dis_h.inter_type_h = 'N';
		rays[i].dis_v.inter_type_v = 'N';
		dis = cal_distance(data, &rays[i].dis_h, &rays[i].dis_v, rayangle);
		dis = dis * cos(data->player.angle - rayangle);
		line_height = (SIZE / dis) * (WIDTH / 2) / tan(FOV / 2);
		rays[i].rayangle = rayangle;
		draw_3d(data, line_height, i, rays[i]);
		rayangle += angle;
		i++;
	}
	free(rays);
}
