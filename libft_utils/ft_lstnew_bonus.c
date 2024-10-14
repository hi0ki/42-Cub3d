/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:25:54 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/12 20:20:43 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_lines	*ft_lstnew(void)
{
	t_lines	*node;

	node = (t_lines *)malloc(sizeof(t_lines));
	if (!node)
		return (NULL);
	node->prv = NULL;
	node->next = NULL;
	return (node);
}
