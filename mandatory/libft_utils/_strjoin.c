/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _strjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:49:39 by kadam             #+#    #+#             */
/*   Updated: 2024/10/18 18:14:38 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*_strjoin(char *s1, char *s2)
{
	char	*str;
	int		dlen;
	int		slen;
	int		i;
	int		j;

	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	if (ft_strlen(s2) == 1 && s2[0] == '\n')
	{
		free(s2);
		printf("Error: Invalid map9\n");
		exit(1);
	}
	dlen = ft_strlen(s1);
	slen = ft_strlen(s2);
	str = malloc((dlen + slen + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[dlen + slen] = '\0';
	free(s1);
	return (str);
}
