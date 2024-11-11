/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:02 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/10 21:29:40 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	h_close_d(t_data *data, t_dis_h *dis_h)
{
	int	xa;
	int	ya;

	xa = dis_h->x_h / SIZE;
	ya = dis_h->y_h / SIZE;
	if (ya < 0 || ya >= ft_lenarray(data->map) || xa >= _strlen(data->map[ya])
		|| xa < 0)
		return (0);
	if (data->map[ya][xa] && data->map[ya][xa] == 'O'
		&& dis_h->close_d == false)
	{
		dis_h->x_o = xa;
		dis_h->y_o = ya;
		dis_h->close_d = true;
	}
	return (0);
}

int	v_close_d(t_data *data, t_dis_v *dis_v)
{
	int	xa;
	int	ya;

	xa = dis_v->x_v / SIZE;
	ya = dis_v->y_v / SIZE;
	if (ya < 0 || ya >= ft_lenarray(data->map) || xa >= _strlen(data->map[ya])
		|| xa < 0)
		return (0);
	if (data->map[ya][xa] && data->map[ya][xa] == 'O'
		&& dis_v->close_d == false)
	{
		dis_v->x_o = xa;
		dis_v->y_o = ya;
		dis_v->close_d = true;
	}
	return (0);
}

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

void	start_raycasting(t_data *data)
{
	double	fov;
	double	rayangle;
	double	angle;
	double	dis;
	double	line_height;
	int		i;
	t_rays	*rays;

	fov = 60 * (M_PI / 180);
	rayangle = data->player.angle - fov / 2;
	angle = fov / WIDTH;
	dis = 0;
	line_height = 0;
	i = 0;
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
		line_height = (SIZE / dis) * (WIDTH / 2) / tan(fov / 2);
		rays[i].rayangle = rayangle;
		draw_3d(data, line_height, i, rays[i]);
		rayangle += angle;
		i++;
	}
	free(rays);
}
