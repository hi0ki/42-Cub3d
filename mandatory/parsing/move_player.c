/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:50:58 by kadam             #+#    #+#             */
/*   Updated: 2024/10/20 12:41:50 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	handle_movement(t_map *map, double *new_px,
		double *new_py)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		*new_px += cos(map->player.angle) * MOVE_SPEED;
		*new_py += sin(map->player.angle) * MOVE_SPEED;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		*new_px -= cos(map->player.angle) * MOVE_SPEED;
		*new_py -= sin(map->player.angle) * MOVE_SPEED;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		*new_px += sin(map->player.angle) * MOVE_SPEED;
		*new_py -= cos(map->player.angle) * MOVE_SPEED;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		*new_px -= sin(map->player.angle) * MOVE_SPEED;
		*new_py += cos(map->player.angle) * MOVE_SPEED;
	}
}

void key_hook(t_map *map)
{
	double	new_px;
	double	new_py;

	new_px = map->player.px;
	new_py = map->player.py;
	handle_movement(map, &new_px, &new_py);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->player.angle -= ROTATION_SPEED;
	else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->player.angle += ROTATION_SPEED;
	else if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		exit(1);
	map->player.angle = fmod(map->player.angle, 2 * M_PI);
	if (map->player.angle < 0)
		map->player.angle += 2 * M_PI;
	if (check_pos(map, new_py, new_px, 4) == 0)
	{
		map->player.px = new_px;
		map->player.py = new_py;
	}
}

void start_key_hook(void *param)
{
    t_map *map = (t_map *)param;
    key_hook(map);
}