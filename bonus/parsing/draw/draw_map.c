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

static void	draw_line(void *image, int x, int y, double angle)
{
	int		y1;
	int		x1;
	double	i;

	i = 0;
	x1 = 0;
	y1 = 0;
	while (i < 6)
	{
		y1 = y + i * sin(angle);
		x1 = x + i * cos(angle);
		if (y1 >= 0 && y1 < HEIGHT && x1 >= 0 && x1 < WIDTH)
			mlx_put_pixel(image, x1, y1, GREEN);
		i++;
	}
}

void	draw_cros(t_data *data)
{
	double	x;
	double	y;

	x = WIDTH / 2;
	y = HEIGHT / 2;
	draw_line(data->image, x - 3, y, M_PI);
	draw_line(data->image, x, y - 3, M_PI_2 * 3);
	draw_line(data->image, x, y + 3, M_PI_2);
	draw_line(data->image, x + 3, y, 0);
}

void	start_drawing(void *ptr)
{
	t_data	*data;

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
