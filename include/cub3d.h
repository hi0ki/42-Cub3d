/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:12:37 by kadam             #+#    #+#             */
/*   Updated: 2024/09/06 08:57:00 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
# include <fcntl.h>
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

int	ft_lenarray(char **array);
void free_2d_array(char **array);
void	ft_putstrn_fd(char *s, int fd);
char	**ft_split(char *s, char *c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
int     _strlen(char *str);
/*                    parsing                      */
int     start_parsing(t_map *map_struct, int ac, char **av);
/*                      utils                   */
bool    find_player(t_map *s_map);
void	check_map(t_map *s_map);
char	**copy_arr(char **array);
void	put_err(char *str, t_map *s_map);
/*				check_utils						*/
int valid_char(char **arr, t_map *s_map);
int found_zero_index(char **arr, t_map *s_map);
int valid_path(char **map, int y, int x);

#endif