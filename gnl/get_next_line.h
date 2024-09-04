/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:00:20 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/09/04 12:14:09 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include "../include/cub3d.h"

char	*get_next_line(int fd);
char	*ft_save(char *save);
char	*ft_line(char *save);
char	*ft_read(int fd, char *save);
int		ft_strlen(char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		chr_n(char *str);

#endif
