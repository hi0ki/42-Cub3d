/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:48:43 by kadam             #+#    #+#             */
/*   Updated: 2024/10/15 18:04:00 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_square(void *image, int x, int y, int size, int color)
{
    int i = 0, j = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_put_pixel(image, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_line(void *image, int x, int y, double size, int color, double angle)
{
    int y1 = 0, x1 = 0;

    for (double i = 0; i < size; i++)
    {
        y1 = y + i * sin(angle);
        x1 = x + i * cos(angle);
        if (y1 >= 0 && y1 < HEIGHT && x1 >= 0 && x1 < WIDTH)
            mlx_put_pixel(image, x1, y1, color);
    }
}

void draw_player(void *image, int x, int y, int size, int color)
{
    int i = 0, j = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_put_pixel(image, x + i, y + j, color);
            j++;
        }
        i++;
    }
    i = 0;
    j = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_put_pixel(image, x - i, y + j, color);
            j++;
        }
        i++;
    }
}

void draw_minimap(t_map *map)
{
    if (map->player.image_player)
    {
        mlx_delete_image(map->mlx, map->player.image_player);
    }
    map->player.image_player = mlx_new_image(map->mlx, 100, 100);
    int x = 0, y = 0;
    while (map->map_array[y])
    {
        x = 0;
        while (map->map_array[y][x])
        {
            if (ft_strchr("WESN10", map->map_array[y][x]))
                draw_square(map->image, x * Size, y * Size, Size, 0xFFFFFFFF);
            x++;
        }
        y++;
    }
    x = 0, y = 0;
    mlx_image_to_window(map->mlx, map->player.image_player, 0, 0);
}

static int color_pixel(int *arr, int index)
{
    if (index == 0)
        return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | arr[3]);
    else
        return ((arr[0] << 24) | (arr[1] << 16) | (arr[2] << 8) | 0xFF);
}

void draw_cros(t_map *map)
{
    double x = WIDTH / 2;
    double y = HEIGHT / 2;
    draw_line(map->image, x - 3, y, 6, RED, M_PI);       // lift
    draw_line(map->image, x, y - 3, 6, RED, M_PI_2 * 3); // top
    draw_line(map->image, x, y + 3, 6, RED, M_PI_2);     // bot
    draw_line(map->image, x + 3, y, 6, RED, 0);          // right
}

void draw_gun(t_map *map, int in)
{
    int arr[4];
    int i = 0;
    int j = 0;
    int index = 0;
    int height = map->gun[in]->height;
    int width = map->gun[in]->width;
    int scale_factor = 4;
    int x_c = WIDTH / 2 - (width * scale_factor) / 2;
    int y_c = HEIGHT - (height * scale_factor);
    if (height * scale_factor > HEIGHT || width * scale_factor > WIDTH)
    {
        ft_putstrn_fd("The gun is too big for the game window.", 2);
        return;
    }
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            arr[0] = map->gun[in]->pixels[index];
            arr[1] = map->gun[in]->pixels[index + 1];
            arr[2] = map->gun[in]->pixels[index + 2];
            arr[3] = map->gun[in]->pixels[index + 3];
            if (arr[0] || arr[1] || arr[2] || arr[3])
            {
                int k = 0;
                while (k < scale_factor)
                {
                    int l = 0;
                    while (l < scale_factor)
                    {
                        mlx_put_pixel(map->image, x_c + (j * scale_factor) + l, y_c + (i * scale_factor) + k, color_pixel(arr, 0));
                        l++;
                    }
                    k++;
                }
            }
            j++;
            index += 4;
        }
        i++;
    }
}

void start_drawing(void *ptr)
{
    t_map *map = (t_map *)ptr;

    mlx_delete_image(map->mlx, map->image);
    map->image = mlx_new_image(map->mlx, WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT / 2; y++)
    {
        for (int x = 0; x < WIDTH; x++)
            mlx_put_pixel(map->image, x, y, color_pixel(map->C, 1));
    }
    for (int y = HEIGHT / 2; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
            mlx_put_pixel(map->image, x, y, color_pixel(map->F, 1));
    }
    map->player.angle = fmod(map->player.angle, 2 * M_PI);
    if (map->player.angle < 0)
        map->player.angle += 2 * M_PI;
    start_raycasting(map);
    mlx_image_to_window(map->mlx, map->image, 0, 0);
    draw_cros(map);
    static int frame ;
    static int counter;
    if (map->index == 1 && frame <= 6)
    {
        draw_gun(map, frame % 7);
        if (counter % 4 == 0)
            frame++;
        counter++;
        if (frame == 7)
            map->index = 2;
    }
    else
    {
        draw_gun(map, 0);
        frame = 0;
        counter = 0;
    }
}