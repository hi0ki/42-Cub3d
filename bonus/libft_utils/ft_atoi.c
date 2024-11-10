/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:25:16 by kadam             #+#    #+#             */
/*   Updated: 2024/11/10 18:36:24 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	atoi_helper(const char *str, int i)
{
	if (str[i] == '+')
	{
		if (str[i + 1] && (str[i + 1] == '-' || str[i + 1] == '+'))
			return (-1);
		return (0);
	}
	return (2);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	old;
	int	i;

	result = 0;
	old = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	if (!atoi_helper(str, i))
		i++;
	else if (atoi_helper(str, i) == -1)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		old = result;
		result = result * 10 + str[i] - '0';
		if (old != (result / 10))
			return (-1);
		i++;
	}
	return (result);
}
