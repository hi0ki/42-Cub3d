/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:12:37 by kadam             #+#    #+#             */
/*   Updated: 2024/09/06 11:34:13 by kadam            ###   ########.fr       */
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
#include "../gnl/get_next_line.h"
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_map
{
    // read the map
    char **map_array;
    // read the path
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    // read the color
    int F[3];
    int C[3];
    
} t_map;

int ft_lenarray(char **array);
void free_2d_array(char **array);
void ft_putstrn_fd(char *s, int fd);
char **ft_split(char *s, char *c);
char *ft_substr(char const *s, size_t start, size_t len);
char *ft_strtrim(char const *s1, char const *set);
int ft_strcmp(const char *s1, const char *s2);
int ft_atoi(const char *str);
char	*_strjoin(char *s1, char *s2);
/*                    parsing                      */
int check_all(int ac, char **av, t_map *map_struct, int fd);

#endif