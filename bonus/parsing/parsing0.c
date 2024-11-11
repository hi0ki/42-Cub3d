/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:24:38 by kadam             #+#    #+#             */
/*   Updated: 2024/11/11 12:14:44 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	read_file(int fd, t_helper *helper)
{
	while (helper->line != NULL)
	{
		helper->trim_line = ft_strtrim(helper->line, " \t\v\f\r");
		if (!ft_strcmp(helper->trim_line, "\n"))
		{
			free(helper->trim_line);
			free(helper->line);
			helper->line = get_next_line(fd);
			continue ;
		}
		else
		{
			helper->res = process_line(helper->trim_line, &helper->ptr_line,
					helper->find);
			free(helper->trim_line);
			if (helper->res == 0)
				break ;
			else if (helper->res == 1)
				return (free(helper->line), free(helper->ptr_line), 1);
		}
		free(helper->line);
		helper->line = get_next_line(fd);
	}
	return (0);
}
