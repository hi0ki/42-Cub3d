/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
/*   Updated: 2024/10/31 12:49:09 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	start_drawing(void *ptr)
{
	t_data	*data;

	map = (t_data *)ptr;
	mlx_delete_image(datamlx, dataimage);
	dataimage = mlx_new_image(datamlx, WIDTH, HEIGHT);
	draw_f_c(map);
	dataplayer.angle = fmod(dataplayer.angle, 2 * M_PI);
	if (dataplayer.angle < 0)
		dataplayer.angle += 2 * M_PI;
	start_raycasting(map);
	mlx_image_to_window(datamlx, dataimage, 0, 0);
}
