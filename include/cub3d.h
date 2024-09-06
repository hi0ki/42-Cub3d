/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:12:37 by kadam             #+#    #+#             */
/*   Updated: 2024/09/06 12:55:39 by kadam            ###   ########.fr       */
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

typedef struct s_player
{
	int x;
	int y;
}t_player;
typedef struct s_map
{
	//read the all map
	char    **str;
	//read the map
	char	**map_array;
	//read the path
	char    *NO;
	char    *SO;
	char    *WE;
	char    *EA;
	//read the color
	int     F[3];
	int     C[3];
	//for player
	t_player player;
}	t_map;

int ft_lenarray(char **array);
void free_2d_array(char **array);
void	ft_putstrn_fd(char *s, int fd);
char	**ft_split(char *s, char *c);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*ft_strchr(char *s, int c);
char *ft_strtrim(char const *s1, char const *set);
int ft_strcmp(const char *s1, const char *s2);
int ft_atoi(const char *str);
char	*_strjoin(char *s1, char *s2);
int     _strlen(char *str);
/*                    parsing                      */
int check_all(int ac, char **av, t_map *map_struct, int fd);
/*                      utils                   */
void	check_map(t_map *s_map);
char	**copy_arr(char **array);
void	put_err(char *str, t_map *s_map);
/*				check_utils						*/
int valid_char(char **arr, t_map *s_map);
int found_zero_index(char **arr, t_map *s_map);
int valid_path(char **map, int y, int x);

#endif