/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _strjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:49:39 by kadam             #+#    #+#             */
/*   Updated: 2024/11/08 13:50:37 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*ft_cpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*_strjoin(char *s1, char *s2)
{
	char	*str;
	int		dlen;
	int		slen;

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
	ft_cpy(str, s1, dlen);
	ft_cpy(str + dlen, s2, slen);
	str[dlen + slen] = '\0';
	free(s1);
	return (str);
}
