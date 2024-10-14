#include "../include/cub3d.h"

void draw_top(t_map *map, t_lines *lines)
{
    double xsize = 20;
    double ysize = 90 + 20;
    t_lines *tmp;

    tmp = lines;
    while (ysize >= 0 && tmp)
    {
        xsize = 20;
        while (map->map_array[tmp->y][tmp->s_x] && tmp->s_x <= tmp->e_x)
        {
            if (map->map_array[tmp->y][tmp->s_x] == '1')   
                draw_square(map->image, xsize, ysize, Size, BLACK);
            else if (ft_strchr("NWSE0", map->map_array[tmp->y][tmp->s_x]))
                draw_square(map->image, xsize, ysize, Size, WHITE);
            xsize += Size;
            tmp->s_x++;
        }
        ysize -= Size;
        tmp = tmp->prv;
    }
}

void draw_bot(t_map *map, t_lines *lines)
{
    double xsize = 20;
    double ysize = 120 + 20;
    t_lines *tmp;

    tmp = lines->next;
    while (ysize < 230 && tmp)
    {
        xsize = 20;
        while (map->map_array[tmp->y][tmp->s_x] && tmp->s_x <= tmp->e_x)
        {
            if (map->map_array[tmp->y][tmp->s_x] == '1')   
                draw_square(map->image, xsize, ysize, Size, BLACK);
            else if (map->map_array[tmp->y][tmp->s_x] == '0' || ft_strchr("NWSE", map->map_array[tmp->y][tmp->s_x]))
                draw_square(map->image, xsize, ysize, Size, WHITE);
            xsize += Size;
            tmp->s_x++;
        }
        ysize += Size;
        tmp = tmp->next;
    }
}

void draw_background(t_map *map)
{
    double x;
    double y;
    
    y = 18;
    while (y < 232)
    {
        x = 18;
        while (x < 232)
        {
            if (y < 20 || x < 20 || (y > 230 && y < 232) || (x > 230 && x < 232))
                mlx_put_pixel(map->image, x, y, NEW);
            else
                mlx_put_pixel(map->image, x, y, GREY);
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

void end_x(t_map *map, t_lines *node, int x, int len)
{
    int j;

    j = 0;
    while (map->map_array[node->y][x] && j < len)
    {
        x++;
        j++;
    }
    node->e_x = x;
}
