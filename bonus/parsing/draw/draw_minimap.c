/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:06:54 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/11 12:05:59 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	minimap_top(t_data *data, t_lines **lines, int len)
{
	int		x;
	int		y;
	int		i;
	t_lines	*node;

	i = 0;
	y = data->player.py / SIZE;
	x = data->player.px / SIZE;
	while (y > 0 && i < len)
	{
		y--;
		i++;
	}
	while (y < ft_lenarray(data->map) && i >= 0)
	{
		node = ft_lstnew();
		node->y = y;
		node->x_pos = x;
		start_x(node, x, len);
		end_x(data, node, x, len);
		ft_lstadd_back(lines, node);
		y++;
		i--;
	}
}

static void	minimap_bot(t_data *data, t_lines **lines, int len)
{
	int		x;
	int		y;
	int		i;
	t_lines	*node;

	i = 0;
	y = data->player.py / SIZE + 1;
	x = data->player.px / SIZE;
	while (y < ft_lenarray(data->map) && i < len)
	{
		node = ft_lstnew();
		node->y = y;
		node->x_pos = x;
		start_x(node, x, len);
		end_x(data, node, x, len);
		ft_lstadd_back(lines, node);
		y++;
		i++;
	}
}

static void	drawing_mini(t_data *data, t_lines *lines)
{
	t_lines	*tmp;

	tmp = lines;
	while (tmp)
	{
		if (tmp->y == (int)data->player.py / SIZE)
		{
			draw_top(data, tmp);
			draw_bot(data, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	draw_player(void *image, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(image, x + i, y + j, RED);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	t_lines	*lines;
	t_lines	*tmp;

	tmp = NULL;
	lines = NULL;
	minimap_top(data, &lines, 5);
	minimap_bot(data, &lines, 5);
	drawing_mini(data, lines);
	while (lines)
	{
		tmp = lines->next;
		free(lines);
		lines = tmp;
	}
	draw_player(data->image, 110 + 20, 110 + 20);
}
