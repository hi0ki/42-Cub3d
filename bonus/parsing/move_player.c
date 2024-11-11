/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:44:52 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/11 12:14:29 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	handle_movement(t_data *data, double *new_px, double *new_py)
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		if (data->index == 0 || data->index == 2)
			data->index = 1;
	}
}

static void	door_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	t_rays	ray;

	data = (t_data *)param;
	ray.dis_h.close_d = false;
	ray.dis_v.close_d = false;
	ray.dis_h.open_d = false;
	ray.dis_v.open_d = false;
	cal_distance(data, &ray.dis_h, &ray.dis_v, data->player.angle);
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		open_door(data, ray, 0, 0);
	else if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		close_door(data, ray);
}

static void	key_hook(t_data *data)
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

void	start_key_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	key_hook(data);
	mlx_key_hook(data->mlx, door_keyhook, data);
}
