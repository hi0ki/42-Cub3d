/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:54:47 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/09/06 14:45:00 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int floodfill(char **map, int y, int x)
{
	if (!map[y][x] || map[y][x] == '1')
		return (0);
	if (map[y][x] != '1')
	{
		if (valid_path(map, y, x) == -1)
		{
			return (-1);
		}
	}
	if (map[y][x] != '1')
		map[y][x] = '1';
	if (floodfill(map, y + 1, x) == -1)
        return (-1);
    if (floodfill(map, y - 1, x) == -1)
        return (-1);
    if (floodfill(map, y, x + 1) == -1)
        return (-1);
    if (floodfill(map, y, x - 1) == -1)
        return (-1);
	return (0);
}


void print_array(char **arr)
{
    int i = 0;
    while (arr[i])
    {
        printf("%s\n", arr[i]);
        i++;
    }
}

void check_map(t_map *s_map)
{
	char **cpy_arr;

	if (valid_char(s_map->map_array, s_map) == -1)
		put_err("Error: No direction in the map.", s_map);
	cpy_arr = copy_arr(s_map->map_array);
	while (found_zero_index(cpy_arr, s_map))
	{
		if (floodfill(cpy_arr, s_map->player.y, s_map->player.x))
		{
			put_err("Error: Invalid map.", s_map);
			free_2d_array(cpy_arr);
		}
	}
	// print_array(cpy_arr);
	free_2d_array(cpy_arr);
}
