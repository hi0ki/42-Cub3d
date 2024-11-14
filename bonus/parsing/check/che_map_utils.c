/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   che_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:57:59 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/14 16:27:48 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	door_helper(char **data, int y, int x)
{
	if ((data[y][x - 1] == '1' && data[y][x + 1] == '1') || 
		(data[y - 1][x] == '1' && data[y + 1][x] == '1'))
		return (1);
	return (0);
}

int	check_door(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'D')
			{
				if (!door_helper(data->map, y, x))
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	valid_path(char **map, int y, int x)
{
	if (!ft_strchr("1 ", map[y][x]) && (y == 0 || y == ft_lenarray(map) - 1))
		return (-1);
	if (!ft_strchr("1 ", map[y][x]) && (x == 0 || x == _strlen(map[y]) - 1))
		return (-1);
	if (!map[y][x + 1] || !ft_strchr("1WESN0D", map[y][x + 1]))
		return (-1);
	if (!ft_strchr("1WESN0D", map[y][x - 1]))
		return (-1);
	if (y > 0 && (x >= _strlen(map[y - 1]) || 
			!ft_strchr("1WESN0D", map[y - 1][x])))
		return (-1);
	if (y != ft_lenarray(map) - 1 && (x >= _strlen(map[y + 1])
			|| !ft_strchr("1WESN0D", map[y + 1][x])))
		return (-1);
	if (map[y][x] == '0' && (y == 0 || y == ft_lenarray(map) - 1))
		return (-1);
	return (0);
}

int	found_zero_index(char **arr, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			if (ft_strchr("WESN0D", arr[y][x]))
			{
				data->player.x = x;
				data->player.y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	valid_char(char **arr, t_data *data)
{
	int		y;
	int		x;
	bool	is_exist;

	y = 0;
	is_exist = true;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			if (ft_strchr("WESN", arr[y][x]) && is_exist == true)
				is_exist = false;
			else if (ft_strchr("WESN", arr[y][x]) && is_exist == false)
				put_err("Error: Multiple directions.", data);
			x++;
		}
		y++;
	}
	if (is_exist == true)
		return (-1);
	return (0);
}
