/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:00:58 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/09/06 08:57:09 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**copy_arr(char **array)
{
	int		i;
	int		y;
	char	**arr;

	i = 0;
	y = ft_lenarray(array);
	arr = malloc((y + 1) * sizeof(char *));
	while (array[i])
	{
		arr[i] = ft_strdup(array[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void put_err(char *str, t_map *s_map)
{
	ft_putstrn_fd(str, 2);
	(void)s_map;
	exit(EXIT_FAILURE);
}