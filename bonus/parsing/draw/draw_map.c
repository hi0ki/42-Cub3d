/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
/*   Updated: 2024/11/10 22:07:34 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_square(void *image, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(void *image, int x, int y, double size, int color,
		double angle)
{
	int y1;
	int x1;

	x1 = 0;
	y = 1;
	for (double i = 0; i < size; i++)
	{
		y1 = y + i * sin(angle);
		x1 = x + i * cos(angle);
		if (y1 >= 0 && y1 < HEIGHT && x1 >= 0 && x1 < WIDTH)
			mlx_put_pixel(image, x1, y1, color);
	}
}

void	draw_cros(t_data *data)
{
	double x = WIDTH / 2;
	double y = HEIGHT / 2;
	draw_line(data->image, x - 3, y, 6, GREEN, M_PI);
	draw_line(data->image, x, y - 3, 6, GREEN, M_PI_2 * 3);
	draw_line(data->image, x, y + 3, 6, GREEN, M_PI_2);
	draw_line(data->image, x + 3, y, 6, GREEN, 0);
}

void	start_drawing(void *ptr)
{
	t_data		*data;

	data = (t_data *)ptr;
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->player.angle = fmod(data->player.angle, 2 * M_PI);
	if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	draw_f_c(data);
	start_raycasting(data);
	draw_cros(data);
	draw_background(data);
	draw_minimap(data);
	helper_gun(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
