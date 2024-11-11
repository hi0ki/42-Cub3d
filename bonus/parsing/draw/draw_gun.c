/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
/*   Updated: 2024/11/10 22:07:34 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	init_gun(t_gun *gun, t_data *data, int in)
{
	gun->i = 0;
	gun->j = 0;
	gun->index = 0;
	gun->height = data->gun[in]->height;
	gun->width = data->gun[in]->width;
	gun->scale_factor = 4;
	gun->x_c = WIDTH / 2 - (gun->width * gun->scale_factor) / 2;
	gun->y_c = HEIGHT - (gun->height * gun->scale_factor);
	if (gun->height * gun->scale_factor > HEIGHT || gun->width
		* gun->scale_factor > WIDTH)
	{
		ft_putstrn_fd("The gun is too big for the game window.", 2);
		return (1);
	}
	gun->k = 0;
	gun->l = 0;
	return (0);
}

static int	color_pixel(int *arr)
{
	return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | arr[3]);
}

static void	draw_scaled_pixel(t_data *data, t_gun *gun)
{
	gun->k = 0;
	while (gun->k < gun->scale_factor)
	{
		gun->l = 0;
		while (gun->l < gun->scale_factor)
		{
			mlx_put_pixel(data->image, gun->x_c + (gun->j * gun->scale_factor)
				+ gun->l, gun->y_c + (gun->i * gun->scale_factor) + gun->k,
				color_pixel(gun->arr));
			gun->l++;
		}
		gun->k++;
	}
}

static void	draw_gun(t_data *data, int in)
{
	t_gun	gun;

	if (init_gun(&gun, data, in))
		return ;
	while (gun.i < gun.height)
	{
		gun.j = 0;
		while (gun.j < gun.width)
		{
			gun.arr[0] = data->gun[in]->pixels[gun.index];
			gun.arr[1] = data->gun[in]->pixels[gun.index + 1];
			gun.arr[2] = data->gun[in]->pixels[gun.index + 2];
			gun.arr[3] = data->gun[in]->pixels[gun.index + 3];
			if (gun.arr[0] || gun.arr[1] || gun.arr[2] || gun.arr[3])
				draw_scaled_pixel(data, &gun);
			gun.j++;
			gun.index += 4;
		}
		gun.i++;
	}
}

void	helper_gun(t_data *data)
{
	static int	frame;
	static int	counter;

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
}
