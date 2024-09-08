/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:46:15 by kadam             #+#    #+#             */
/*   Updated: 2024/09/08 17:13:03 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"


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

void draw_border(void *image, int x, int y, int size, int color)
{
    int i = 0, j = 0;
    while (i < size)
    {
        mlx_put_pixel(image, x + i, y, color);
        mlx_put_pixel(image, x + i, y + size - 1, color);
        i++;
    }
    while (j < size)
    {
        mlx_put_pixel(image, x, y + j, color);
        mlx_put_pixel(image, x + size - 1, y + j, color);
        j++;
    }
}

void draw_line(void *image, int x, int y, int size, int color, float angle)
{
    int y1 = 0, x1 = 0;
    for (int i = 0; i < size; i++)
    {
        y1 = y + i * sin(angle);
        x1 = x + i * cos(angle);
        mlx_put_pixel(image, x1, y1, color);
    }
}

void draw_map(t_map *map)
{
    int x = 0, y = 0;
    while (map->map_array[y])
    {
        x = 0;
        while (map->map_array[y][x])
        {
            if (ft_strchr("WESN10", map->map_array[y][x]))
            {
                draw_square(map->image, x * Size, y * Size, Size, 0xFFFFFFFF);
                draw_border(map->image, x * Size, y * Size, Size, 0x000000FF);
            }
            x++;
        }
        y++;
    }
    x = 0;
    y = 0;
    while (map->map_array[y])
    {
        x = 0;
        while (map->map_array[y][x])
        {
            if (map->map_array[y][x] == '1')
                draw_square(map->image, x * Size, y * Size, Size, 0x000000FF);
            else if (ft_strchr("WESN", map->map_array[y][x]))
            {
                mlx_put_pixel(map->player.image_player, x * Size, y * Size, 0xFF0000FF);
                draw_line(map->player.image_player, x * Size, y * Size, 16, 0xFF0000FF, map->player.angle);
            }
            x++;
        }
        y++;
    }
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_map *map = (t_map *)param;
    float move_speed = MOVE_SPEED;
    float new_px = map->player.px;
    float new_py = map->player.py;

    if (keydata.key == MLX_KEY_W && keydata.action)
    {
        new_px += cos(map->player.angle) * move_speed;
        new_py += sin(map->player.angle) * move_speed;
    }
    else if (keydata.key == MLX_KEY_S && keydata.action)
    {
        new_px -= cos(map->player.angle) * move_speed;
        new_py -= sin(map->player.angle) * move_speed;
    }
    else if (keydata.key == MLX_KEY_A && keydata.action)
    {
        new_px -= cos(map->player.angle + M_PI_2) * move_speed;
        new_py -= sin(map->player.angle + M_PI_2) * move_speed;
    }
    else if (keydata.key == MLX_KEY_D && keydata.action)
    {
        new_px += cos(map->player.angle + M_PI_2) * move_speed;
        new_py += sin(map->player.angle + M_PI_2) * move_speed;
    }
    else if (keydata.key == MLX_KEY_LEFT && keydata.action)
        map->player.angle -= ROTATION_SPEED;
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action)
        map->player.angle += ROTATION_SPEED;
    else if (keydata.key == MLX_KEY_ESCAPE && keydata.action)
        exit(1);
    int map_x = new_px / Size;
    int map_y = new_py / Size;
    if (map->map_array[map_y][map_x] != '1')
    {
        mlx_delete_image(map->mlx, map->player.image_player);
        map->player.image_player = mlx_new_image(map->mlx, 1920, 1080);
        map->player.px = new_px;
        map->player.py = new_py;
        mlx_put_pixel(map->player.image_player, map->player.px, map->player.py, 0xFF0000FF);
        draw_line(map->player.image_player, map->player.px, map->player.py, 16, 0xFF0000FF, map->player.angle);
        mlx_image_to_window(map->mlx, map->player.image_player, 340, 240);
    }
}

int main(int ac, char **av)
{
    t_map map_struct;
    int fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return (ft_putstrn_fd("Error: Unable to open file", 2), 1);
    if (check_all(ac, av, &map_struct, fd))
        return (close(fd), 1);
    close(fd);
    check_map(&map_struct);
    map_struct.player.angle = 0;
    map_struct.player.px = -1;
    map_struct.player.py = -1;
    int x = 0, y = 0;
    while (map_struct.map_array[y])
    {
        x = 0;
        while (map_struct.map_array[y][x])
        {
            if (ft_strchr("WESN", map_struct.map_array[y][x]))
            {
                if (map_struct.map_array[y][x] == 'N')
                    map_struct.player.angle = 270 * (M_PI / 180);
                else if (map_struct.map_array[y][x] == 'E')
                    map_struct.player.angle = 0;
                else if (map_struct.map_array[y][x] == 'S')
                    map_struct.player.angle = 90 * (M_PI / 180);
                else if (map_struct.map_array[y][x] == 'W')
                    map_struct.player.angle = 180 * (M_PI / 180);
                map_struct.player.px = x * Size;
                map_struct.player.py = y * Size;
                break;
            }
            x++;
        }
        y++;
    }
    map_struct.mlx = mlx_init(1920, 1080, "Cub3D", true);
    map_struct.image = mlx_new_image(map_struct.mlx, 1920, 1080);
    map_struct.player.image_player = mlx_new_image(map_struct.mlx, 1920, 1080);
    draw_map(&map_struct);
    mlx_image_to_window(map_struct.mlx, map_struct.image, 340, 240);
    mlx_image_to_window(map_struct.mlx, map_struct.player.image_player, 340, 240);
    mlx_key_hook(map_struct.mlx, &key_hook, &map_struct);
    mlx_loop(map_struct.mlx);
    return (0);
}
