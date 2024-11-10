/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:35:57 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/10 17:57:37 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*dest;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (start >= (size_t)ft_strlen(s))
		return (dest = ft_strdup(""), dest);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len)
		dest[i++] = s[start++];
	dest[len] = '\0';
	return (dest);
}
