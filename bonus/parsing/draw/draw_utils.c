/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:07:02 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/06 13:43:03 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void draw_lift(t_data *data, t_lines *tmp, double xsize, double ysize)
{
    int i;

    i = 0;
    while (tmp->x_pos - i >= tmp->s_x)
    {
        if (data->map[tmp->y][tmp->x_pos - i] == '1' && tmp->x_pos - i < _strlen(data->map[tmp->y])) 
        draw_square(data->image, xsize, ysize, SIZE, BLACK);
        else if (ft_strchr("NWSE0", data->map[tmp->y][tmp->x_pos - i]) && tmp->x_pos - i < _strlen(data->map[tmp->y]))
        draw_square(data->image, xsize, ysize, SIZE, WHITE);
        else if (data->map[tmp->y][tmp->x_pos - i] == 'D' && tmp->x_pos - i < _strlen(data->map[tmp->y]))
        draw_square(data->image, xsize, ysize, SIZE, GREEN);
        xsize -= SIZE;
        i++;
    }
}

void draw_right(t_data *data, t_lines *tmp, double xsize, double ysize)
{
    int i;

    i = 1;
    while (tmp->x_pos + i < _strlen(data->map[tmp->y]) && tmp->x_pos + i <= tmp->e_x)
    {
        if (data->map[tmp->y][tmp->x_pos + i] == '1')   
        draw_square(data->image, xsize, ysize, SIZE, BLACK);
        else if (ft_strchr("NWSE0", data->map[tmp->y][tmp->x_pos + i]))
        draw_square(data->image, xsize, ysize, SIZE, WHITE);
        else if (data->map[tmp->y][tmp->x_pos + i] == 'D')   
        draw_square(data->image, xsize, ysize, SIZE, GREEN);
        xsize += SIZE;
        i++;
    }
}
void draw_top(t_data *data, t_lines *lines)
{
    double ysize;
    t_lines *tmp;

    tmp = lines;
    ysize = 100 + 20;
    while (ysize >= 0 && tmp)
    {
        draw_lift(data, tmp, 100 + 20, ysize);
        draw_right(data, tmp, 120 + 20, ysize);
        ysize -= SIZE;
        tmp = tmp->prv;
    }
}

void draw_bot(t_data *data, t_lines *lines)
{
    double ysize;
    t_lines *tmp;

    tmp = lines->next;
    ysize = 120 + 20;
    while (ysize < 240 && tmp)
    {
        draw_lift(data, tmp, 100 + 20, ysize);
        draw_right(data, tmp, 120 + 20, ysize);
        ysize += SIZE;
        tmp = tmp->next;
    }
}

void draw_background(t_data *data)
{
    double x;
    double y;
    
    y = 18;
    while (y < 242)
    {
        x = 18;
        while (x < 242)
        {
            if (y < 20 || x < 20 || y >= 240 || x >= 240)
                mlx_put_pixel(data->image, x, y, NEW);   
            else
                mlx_put_pixel(data->image, x, y, GREY);
            x++;
        }
        y++;
    }
}

void start_x(t_lines *node, int x, int len)
{
    int j;

    j = 0;
    while (x > 0 && j < len)
    {
        x--;
        j++;
    }
    node->s_x = x;
}

void end_x(t_data *data, t_lines *node, int x, int len)
{
    int j;

    j = 0;
    while (data->map[node->y][x] && j < len)
    {
        x++;
        j++;
    }
    node->e_x = x;
}
