/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:00:20 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/09/06 12:52:33 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 20
#endif

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/cub3d.h"

char *get_next_line(int fd);
char *ft_save(char *save);
char *ft_line(char *save);
char *ft_read(int fd, char *save);
size_t ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int chr_n(char *str);

#endif
