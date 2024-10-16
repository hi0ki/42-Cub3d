/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:06:54 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/10/15 20:06:55 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void minimap_top(t_map *map, t_lines **lines, int len)
{
    int x, y;
    int i = 0;
    t_lines *node;

    y = map->player.py / Size;
    x = map->player.px / Size;
    while(y > 0 &&  i < len)
    {
        y--;
        i++;
    }
    while (y < ft_lenarray(map->map_array) &&  i >= 0)
    {
        node = ft_lstnew();
        node->y = y;
        node->x_pos = x;
        start_x(node, x, len);
        end_x(map, node, x, len);
        ft_lstadd_back(lines, node);
        y++;
        i--;
    }
}

static void minimap_bot(t_map *map, t_lines **lines, int len)
{
    int x, y;
    int i = 0;
    t_lines *node;

    y = map->player.py / Size + 1;
    x = map->player.px / Size;
    while (y < ft_lenarray(map->map_array) &&  i < len)
    {
        node = ft_lstnew();
        node->y = y;
        node->x_pos = x;
        start_x(node, x, len);
        end_x(map, node, x, len);
        ft_lstadd_back(lines, node);
        y++;
        i++;
    }
}

static void drawing_mini(t_map *map, t_lines *lines)
{
    t_lines *tmp;

    tmp = lines;
    while (tmp)
    {
        if (tmp->y == (int)map->player.py / Size)
        {
            draw_top(map, tmp);
            draw_bot(map, tmp);
            break;
        }
        tmp = tmp->next;
    }
}

void draw_minimap(t_map *map)
{
    t_lines *lines = NULL;

    minimap_top(map, &lines, 3);
    minimap_bot(map, &lines, 3);
    drawing_mini(map, lines);
    draw_square(map->image, 105 + 20, 105 + 20, 4, RED);
    draw_line(map->image, 105 + 20, 105 + 20, 7, GREEN, map->player.angle);
}