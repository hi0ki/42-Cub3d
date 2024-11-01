/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:50:58 by kadam             #+#    #+#             */
/*   Updated: 2024/10/31 12:49:09 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	handle_movement(t_data *data, double *new_px,
		double *new_py)
{
	if (mlx_is_key_down(datamlx, MLX_KEY_W))
	{
		*new_px += cos(dataplayer.angle) * MOVE_SPEED;
		*new_py += sin(dataplayer.angle) * MOVE_SPEED;
	}
	else if (mlx_is_key_down(datamlx, MLX_KEY_S))
	{
		*new_px -= cos(dataplayer.angle) * MOVE_SPEED;
		*new_py -= sin(dataplayer.angle) * MOVE_SPEED;
	}
	else if (mlx_is_key_down(datamlx, MLX_KEY_A))
	{
		*new_px += sin(dataplayer.angle) * MOVE_SPEED;
		*new_py -= cos(dataplayer.angle) * MOVE_SPEED;
	}
	else if (mlx_is_key_down(datamlx, MLX_KEY_D))
	{
		*new_px -= sin(dataplayer.angle) * MOVE_SPEED;
		*new_py += cos(dataplayer.angle) * MOVE_SPEED;
	}
}

void key_hook(t_data *data)
{
	double	new_px;
	double	new_py;

	new_px = dataplayer.px;
	new_py = dataplayer.py;
	handle_movement(map, &new_px, &new_py);
	if (mlx_is_key_down(datamlx, MLX_KEY_LEFT))
		dataplayer.angle -= ROTATION_SPEED;
	else if (mlx_is_key_down(datamlx, MLX_KEY_RIGHT))
		dataplayer.angle += ROTATION_SPEED;
	else if (mlx_is_key_down(datamlx, MLX_KEY_ESCAPE))
		exit(1);
	dataplayer.angle = fmod(dataplayer.angle, 2 * M_PI);
	if (dataplayer.angle < 0)
		dataplayer.angle += 2 * M_PI;
	if (check_pos(map, new_py, new_px, 4) == 0)
	{
		dataplayer.px = new_px;
		dataplayer.py = new_py;
	}
}

void start_key_hook(void *param)
{
    t_data *data = (t_data *)param;
    key_hook(map);
}