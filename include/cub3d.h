/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:12:37 by kadam             #+#    #+#             */
/*   Updated: 2024/10/15 16:52:45 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "../gnl/get_next_line.h"
#include "types.h"

/*				libft				*/
int ft_lenarray(char **array);
void free_2d_array(char **array);
void ft_putstrn_fd(char *s, int fd);
char **ft_split(char *s, char *c);
char *ft_substr(char const *s, size_t start, size_t len);
char *ft_strchr(char *s, int c);
char *ft_strtrim(char const *s1, char const *set);
int ft_strcmp(const char *s1, const char *s2);
int ft_atoi(const char *str);
char *_strjoin(char *s1, char *s2);
int _strlen(char *str);

/*                    parsing                      */
int check_all(int ac, char **av, t_map *map_struct, int fd);

/*                      utils                   */
void check_map(t_map *s_map);
char **copy_arr(char **array);
void put_err(char *str, t_map *s_map);

/*				check_utils						*/
int valid_char(char **arr, t_map *s_map);
int found_zero_index(char **arr, t_map *s_map);
int valid_path(char **map, int y, int x);
void draw_line(void *image, int x, int y, double size, int color, double angle);
void key_hook(mlx_key_data_t keydata, void *param);
void draw_map(t_map *map);
void draw_player(void *image, int x, int y, int size, int color);

/*					raycasting					*/
void start_raycasting(t_map *map);
int check_ray(t_map *map, double y, double x);
double cal_dis(double xp, double yp, double x, double y);
int check_pos(t_map *map, double py, double px, double num_pix);
void draw_3d(t_map *map, double line_height, int i, t_dis_H *dis_H, t_dis_V *dis_V, int index);
void start_drawing(void *ptr);
void draw_gun(t_map* map, int in);
#endif