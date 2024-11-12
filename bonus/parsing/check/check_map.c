/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:54:47 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/12 16:02:51 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	floodfill(char **data, int row, int col)
{
	if (!data[row][col] || data[row][col] == '1')
		return (0);
	if (data[row][col] != '1')
	{
		if (valid_path(data, row, col) == -1)
			return (-1);
	}
	if (data[row][col] != '1')
		data[row][col] = '1';
	if (floodfill(data, row + 1, col) == -1)
		return (-1);
	if (floodfill(data, row - 1, col) == -1)
		return (-1);
	if (floodfill(data, row, col + 1) == -1)
		return (-1);
	if (floodfill(data, row, col - 1) == -1)
		return (-1);
	return (0);
}

void	check_map(t_data *data)
{
	char	**cpy_arr;

	if (valid_char(data->map, data) == -1)
		put_err("Error: No direction in the map.", data);
	cpy_arr = copy_arr(data->map);
	while (found_zero_index(cpy_arr, data))
	{
		if (floodfill(cpy_arr, data->player.y, data->player.x))
		{
			free_2d_array(cpy_arr);
			put_err("Error: Invalid map.10", data);
		}
	}
	free_2d_array(cpy_arr);
	if (check_door(data))
		put_err("Error: Invalid map.11", data);
}
