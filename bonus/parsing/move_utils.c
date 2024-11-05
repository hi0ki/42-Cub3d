/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:44:52 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/05 13:46:05 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void mouse_hook(void *param)
{
	static int old_x;
	t_data *data;
	int new_y;
	int new_x;

	data = (t_data *)param;
	mlx_set_cursor_mode(data->mlx, 	MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(data->mlx, &new_x, &new_y);
	if (new_x < 0 || new_x > WIDTH || new_y < 0 || new_y > HEIGHT)
	{
		if (new_x < 0)
			new_x = WIDTH;
		if (new_x > WIDTH)
			new_x = 0;
		if (new_y < 0)
			new_y = HEIGHT;
		if (new_y > HEIGHT)
			new_y = 0;
		mlx_set_mouse_pos(data->mlx, new_x, new_y);
	};
	if (new_x - 3 > old_x && new_x != 0 && new_x != WIDTH && new_y != 0 && new_y != HEIGHT)
		data->player.angle += ROTATION_SPEED;
	if (new_x + 3 < old_x && new_x != 0 && new_x != WIDTH && new_y != 0 && new_y != HEIGHT)
		data->player.angle -= ROTATION_SPEED;
	old_x = new_x;
}