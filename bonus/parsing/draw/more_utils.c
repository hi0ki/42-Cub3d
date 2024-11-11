/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:09:36 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/11 12:11:01 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	start_x(t_lines *node, int x, int len)
{
	int	j;

	j = 0;
	while (x > 0 && j < len)
	{
		x--;
		j++;
	}
	node->s_x = x;
}

void	end_x(t_data *data, t_lines *node, int x, int len)
{
	int	j;

	j = 0;
	while (data->map[node->y][x] && j < len)
	{
		x++;
		j++;
	}
	node->e_x = x;
}
