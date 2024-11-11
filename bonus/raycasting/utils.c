/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:21:55 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/11 17:17:42 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	ft_normalize(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

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
