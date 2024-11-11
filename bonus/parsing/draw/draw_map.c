/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/10 22:07:34 by kadam            ###   ########.fr       */
=======
/*   Updated: 2024/11/11 12:05:49 by eel-ansa         ###   ########.fr       */
>>>>>>> hiki
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_square(void *image, int x, int y, int size, int color)
{
	int	i;
<<<<<<< HEAD

	i = 0;
	int j;
=======
	int	j;

	i = 0;
>>>>>>> hiki
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
<<<<<<< HEAD
	int	y1 = 0;
	int	x1 = 0;
=======
	int y1;
	int x1;

	x1 = 0;
	y = 1;
>>>>>>> hiki
	for (double i = 0; i < size; i++)
	{
		y1 = y + i * sin(angle);
		x1 = x + i * cos(angle);
		if (y1 >= 0 && y1 < HEIGHT && x1 >= 0 && x1 < WIDTH)
			mlx_put_pixel(image, x1, y1, color);
	}
}

static int	color_pixel(int *arr, int index)
{
	if (index == 0)
		return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | arr[3]);
	else
		return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | 0xFF);
}

void	draw_cros(t_data *data)
{
<<<<<<< HEAD
	double	x;
	double	y;

	x = WIDTH / 2;
	y = HEIGHT / 2;
=======
	double x = WIDTH / 2;
	double y = HEIGHT / 2;
>>>>>>> hiki
	draw_line(data->image, x - 3, y, 6, GREEN, M_PI);       // lift
	draw_line(data->image, x, y - 3, 6, GREEN, M_PI_2 * 3); // top
	draw_line(data->image, x, y + 3, 6, GREEN, M_PI_2);     // bot
	draw_line(data->image, x + 3, y, 6, GREEN, 0);          // right
}

void	draw_gun(t_data *data, int in)
{
<<<<<<< HEAD
	int	arr[4];
	int	i;
	int	j;
	int	index;
	int	height;
	int	width;
	int	scale_factor;
	int	x_c;
	int	y_c;
	int	k;
	int	l;

	i = 0;
	j = 0;
	index = 0;
	height = data->gun[in]->height;
	width = data->gun[in]->width;
	scale_factor = 4;
	x_c = WIDTH / 2 - (width * scale_factor) / 2;
	y_c = HEIGHT - (height * scale_factor);
	if (height * scale_factor > HEIGHT || width * scale_factor > WIDTH)
	{
		ft_putstrn_fd("The gun is too big for the game window.", 2);
		return ;
=======
	int arr[4];
	int i = 0;
	int j = 0;
	int index = 0;
	int height = data->gun[in]->height;
	int width = data->gun[in]->width;
	int scale_factor = 4;
	int x_c = WIDTH / 2 - (width * scale_factor) / 2;
	int y_c = HEIGHT - (height * scale_factor);
	if (height * scale_factor > HEIGHT || width * scale_factor > WIDTH)
	{
		ft_putstrn_fd("The gun is too big for the game window.", 2);
		return;
>>>>>>> hiki
	}
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			arr[0] = data->gun[in]->pixels[index];
			arr[1] = data->gun[in]->pixels[index + 1];
			arr[2] = data->gun[in]->pixels[index + 2];
			arr[3] = data->gun[in]->pixels[index + 3];
			if (arr[0] || arr[1] || arr[2] || arr[3])
			{
<<<<<<< HEAD
				k = 0;
				while (k < scale_factor)
				{
					l = 0;
					while (l < scale_factor)
					{
						mlx_put_pixel(data->image, x_c + (j * scale_factor) + l,
							y_c + (i * scale_factor) + k, color_pixel(arr, 0));
=======
				int k = 0;
				while (k < scale_factor)
				{
					int l = 0;
					while (l < scale_factor)
					{
						mlx_put_pixel(data->image, x_c + (j * scale_factor) + l, y_c + (i * scale_factor) + k, color_pixel(arr, 0));
>>>>>>> hiki
						l++;
					}
					k++;
				}
			}
			j++;
			index += 4;
		}
		i++;
	}
}

void	start_drawing(void *ptr)
{
	t_data		*data;
<<<<<<< HEAD
	static int	frame;
=======
	static int	frame ;
>>>>>>> hiki
	static int	counter;

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
	if (data->index == 1 && frame <= 6)
	{
		draw_gun(data, frame % 7);
		if (counter % 2 == 0)
			frame++;
		counter++;
		if (frame == 7)
			data->index = 2;
	}
	else
	{
		draw_gun(data, 0);
		frame = 0;
		counter = 0;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
