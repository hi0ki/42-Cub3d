/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:46:15 by kadam             #+#    #+#             */
/*   Updated: 2024/09/06 08:39:28 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int main(int ac, char **av)
{
	static t_map map_struct;

	if (start_parsing(&map_struct, ac, av) == 1)
		return (1);
	check_map(&map_struct);
	// printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", map_struct.NO, map_struct.SO, map_struct.WE, map_struct.EA);
	// printf("F: %d, %d, %d\nC: %d, %d, %d\n", map_struct.F[0], map_struct.F[1], map_struct.F[2], map_struct.C[0], map_struct.C[1], map_struct.C[2]);
	// for (int i = 0; map_struct.map_array[i]; i++)
	// 	printf("%s\n", map_struct.map_array[i]);
	return (0);
}
