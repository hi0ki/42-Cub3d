/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:50:58 by kadam             #+#    #+#             */
/*   Updated: 2024/11/05 13:44:32 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int open_door(t_data *data, int xa, int ya)
{
	t_rays ray;

	ray.dis_H.open_door = false;
	ray.dis_V.open_door = false;
	ray.dis_H.is_door = false;
	ray.dis_V.is_door = false;
	cal_distance(data, &ray.dis_H, &ray.dis_V, data->player.angle);
	if (ray.dis_H.is_door == true)
	{
		xa = ray.dis_H.x_h / SIZE;
		ya = ray.dis_H.y_h / SIZE;
		data->map[ya][xa] = 'O';
	}
	else if (ray.dis_H.open_door == true)
		data->map[ray.dis_H.y_o][ray.dis_H.x_o] = 'D';
	if (ray.dis_V.is_door == true)
	{
		xa = ray.dis_V.x_v / SIZE;
		ya = ray.dis_V.y_v / SIZE;
		data->map[ya][xa] = 'O';
	}
	else if (ray.dis_V.open_door == true)
		data->map[ray.dis_V.y_o][ray.dis_V.x_o] = 'D';
	return (0);
}

static void	handle_movement(t_data *data, double *new_px,
		double *new_py)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		*new_px += cos(data->player.angle) * MOVE_SPEED;
		*new_py += sin(data->player.angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		*new_px -= cos(data->player.angle) * MOVE_SPEED;
		*new_py -= sin(data->player.angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		*new_px += sin(data->player.angle) * MOVE_SPEED;
		*new_py -= cos(data->player.angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		*new_px -= sin(data->player.angle) * MOVE_SPEED;
		*new_py += cos(data->player.angle) * MOVE_SPEED;
	}
}

static void door_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data *data = (t_data *)param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		open_door(data, 0, 0);
}

static void key_hook(t_data *data)
{
	double	new_px;
	double	new_py;

	new_px = data->player.px;
	new_py = data->player.py;
	handle_movement(data, &new_px, &new_py);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle -= ROTATION_SPEED;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle += ROTATION_SPEED;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
	data->player.angle = ft_normalize(data->player.angle);
	if (check_pos(data, new_py, new_px, 4) == 0)
	{
		data->player.px = new_px;
		data->player.py = new_py;
	}
}

void start_key_hook(void *param)
{
    t_data *data = (t_data *)param;

    key_hook(data);
	mlx_key_hook(data->mlx, door_keyhook, data);
}