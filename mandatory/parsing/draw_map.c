/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
/*   Updated: 2024/10/19 14:09:25 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	start_drawing(void *ptr)
{
	t_map	*map;

	map = (t_map *)ptr;
	mlx_delete_image(map->mlx, map->image);
	map->image = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	draw_f_c(map);
	map->player.angle = fmod(map->player.angle, 2 * M_PI);
	if (map->player.angle < 0)
		map->player.angle += 2 * M_PI;
	start_raycasting(map);
	mlx_image_to_window(map->mlx, map->image, 0, 0);
}
