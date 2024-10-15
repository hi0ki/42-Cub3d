/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:54:47 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/05 12:29:34 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int floodfill(char **map, int row, int col)
{
	if (!map[row][col] || map[row][col] == '1')
		return (0);
	if (map[row][col] != '1')
	{
		if (valid_path(map, row, col) == -1)
		{
			printf("wach hna\n");
			return (-1);
		}
	}
	if (map[row][col] != '1')
		map[row][col] = '1';
	if (floodfill(map, row + 1, col) == -1)
        return (-1);
    if (floodfill(map, row - 1, col) == -1)
        return (-1);
    if (floodfill(map, row, col + 1) == -1)
        return (-1);
    if (floodfill(map, row, col - 1) == -1)
        return (-1);
	return (0);
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
			put_err("Error: Invalid map.10", s_map);
			free_2d_array(cpy_arr);
		}
	}
	// print_array(cpy_arr);
	free_2d_array(cpy_arr);
}
