/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:12:37 by kadam             #+#    #+#             */
/*   Updated: 2024/09/04 16:51:06 by kadam            ###   ########.fr       */
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
}	t_map;

int	ft_lenarray(char **array);
void free_2d_array(char **array);
void	ft_putstrn_fd(char *s, int fd);
char	**ft_split(char *s, char *c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*                    parsing                      */
int start_parsing(t_map *map_struct, int ac, char **av);

#endif