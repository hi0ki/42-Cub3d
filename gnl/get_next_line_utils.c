/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:00:32 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/09/04 11:56:47 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*s;

	i = 0;
	dest = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		dlen;
	int		slen;

	if (!s2)
		return (NULL);
	if (ft_strlen(s2) == 1 && s2[0] == '\n')
	{
		free(s2);
		printf("Error: Invalid map >> khsni nbdl hadi\n");
		return (NULL);
	}
	dlen = ft_strlen(s1);
	slen = ft_strlen(s2);
	str = malloc((dlen + slen + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	ft_memcpy(str, s1, dlen);
	ft_memcpy(str + dlen, s2, slen);
	str[dlen + slen] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdup(char *s1)
{
	char	*str;

	str = malloc(ft_strlen(s1) + 1 * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	str[ft_strlen(s1)] = '\0';
	return (str);
}

int	chr_n(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
