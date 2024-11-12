/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:44:52 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/12 15:55:28 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	checkto_open(t_data *data, int y, int x)
{
	int	xa;
	int	ya;

	xa = data->player.px / SIZE;
	ya = data->player.py / SIZE;
	if ((x == xa + 1 || x == xa - 1 || x == xa) && (y == ya + 1 || y == ya - 1
			|| y == ya))
		return (0);
	return (-1);
}

void	open_door(t_data *data, t_rays ray, int xa, int ya)
{
	if (ray.dis_h.open_d == true && ray.dis_h.dis <= 20)
	{
		xa = ray.dis_h.x_h / SIZE;
		ya = ray.dis_h.y_h / SIZE;
		data->map[ya][xa] = 'O';
	}
	if (ray.dis_v.open_d == true && ray.dis_v.dis <= 20)
	{
		xa = ray.dis_v.x_v / SIZE;
		ya = ray.dis_v.y_v / SIZE;
		data->map[ya][xa] = 'O';
	}
}

void	close_door(t_data *data, t_rays ray)
{
	if (ray.dis_h.close_d == true && !checkto_open(data, ray.dis_h.y_o,
			ray.dis_h.x_o))
		data->map[ray.dis_h.y_o][ray.dis_h.x_o] = 'D';
	else if (ray.dis_v.close_d == true && !checkto_open(data, ray.dis_v.y_o,
			ray.dis_v.x_o))
		data->map[ray.dis_v.y_o][ray.dis_v.x_o] = 'D';
}

int	check_to_rot(int new_x, int new_y)
{
	if (new_x != 0 && new_x != WIDTH && new_y != 0 && new_y != HEIGHT)
		return (0);
	return (1);
}

void	mouse_hook(void *param)
{
	static int	old_x;
	t_data		*data;
	int			new_y;
	int			new_x;

	data = (t_data *)param;
	mlx_get_mouse_pos(data->mlx, &new_x, &new_y);
	if (new_x < 0 || new_x > WIDTH || new_y < 0 || new_y > HEIGHT)
	{
		if (new_x < 0)
			new_x = WIDTH;
		if (new_x > WIDTH)
			new_x = 0;
		if (new_y < 0)
			new_y = HEIGHT;
		if (new_y > HEIGHT)
			new_y = 0;
		mlx_set_mouse_pos(data->mlx, new_x, new_y);
	}
	if (new_x > old_x && !check_to_rot(new_x, new_y))
		data->player.angle += ROTATION_SPEED;
	if (new_x < old_x && !check_to_rot(new_x, new_y))
		data->player.angle -= ROTATION_SPEED;
	old_x = new_x;
}
