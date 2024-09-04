/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:25:05 by kadam             #+#    #+#             */
/*   Updated: 2024/09/04 16:50:10 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int check_path(char *str, int len)
{
	if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c' && str[len - 4] == '.')
		return (1);
	return (0);
}

void init_struct(t_map *map_struct)
{
	int i;

	i = 0;
	map_struct->str = NULL;
	map_struct->NO = NULL;
	map_struct->SO = NULL;
	map_struct->WE = NULL;
	map_struct->EA = NULL;
	while (i < 3)
	{
		map_struct->F[i] = -1;
		map_struct->C[i] = -1;
		i++;
	}
	map_struct->map_array = NULL;
}

int read_file(t_map *map_struct, char **av)
{
    char *tmp = NULL;
    char *ptr_line = NULL;
    int fd;

	init_struct(map_struct);
    fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstrn_fd("Error: invalid file", 2);
		exit(1);
	}
	char *line = get_next_line(fd);
	if (line == NULL)
		return (ft_putstrn_fd("Error\nInvalid file : empty file", 2), 1);
	while (line != NULL)
	{
		tmp = ft_strjoin(ptr_line, line);
		line = get_next_line(fd);
		free(ptr_line);
		ptr_line = tmp;
	}
	close(fd);
	map_struct->str = ft_split(ptr_line, "\n");
	free(ptr_line);
	if (map_struct->str == NULL)
		return (1);
	return 0;
}

int process_path(t_map *map_struct, int *i, char *name, char **path)
{
	char **split = ft_split(map_struct->str[*i], " ");
	if (ft_lenarray(split) != 2 || (split[0] && strcmp(split[0], name) != 0))
		return (ft_putstrn_fd("Error: Invalid map", 2), 1);
	*path = ft_strdup(split[1]);
	return 0;
}

int read_path(t_map *map_struct, int *i)
{
	while (map_struct->str[*i] && *i <= 3)
	{
		if (map_struct->str[*i][0] == 'N')
		{
			if (process_path(map_struct, i, "NO", &(map_struct->NO)))
				return 1;
		}
		else if (map_struct->str[*i][0] == 'S')
		{
			if (process_path(map_struct, i, "SO", &(map_struct->SO)))
				return 1;
		}
		else if (map_struct->str[*i][0] == 'W')
		{
			if (process_path(map_struct, i, "WE", &(map_struct->WE)))
				return 1;
		}
		else if (map_struct->str[*i][0] == 'E')
		{
			if (process_path(map_struct, i, "EA", &(map_struct->EA)))
				return 1;
		}
		(*i)++;
	}
	return 0;
}

int process_color(int *map_color, char *str, char *name)
{
	char **split = ft_split(str, " ");
	if (ft_lenarray(split) != 2 || (split[0] && strcmp(split[0], name) != 0))
		return (ft_putstrn_fd("Error: Invalid map", 2), 1);
	char **rgb = ft_split(split[1], ",");
	if (ft_lenarray(rgb) != 3)
		return (ft_putstrn_fd("Error: Invalid map", 2), 1);
	int i = 0;
	while (i < 3)
	{
		map_color[i] = atoi(rgb[i]);
		i++;
	}
	return 0;
}

int read_color(t_map *map_struct, int *i)
{
	while (map_struct->str[*i] && (*i >= 4 && *i <= 5))
	{
		if (map_struct->str[*i][0] == 'F')
		{
			if (process_color(map_struct->F, map_struct->str[*i], "F"))
				return 1;
		}
		else if (map_struct->str[*i][0] == 'C')
		{
			if (process_color(map_struct->C, map_struct->str[*i], "C"))
				return 1;
		}
		(*i)++;
	}
	return 0;
}

int read_map(t_map *map_struct, int *i)
{
	int j = 0;
	int x = *i;
	while (map_struct->str[*i])
	{
		j++;
		(*i)++;
	}
	map_struct->map_array = malloc((j + 1) * sizeof(char *));
	if (map_struct->map_array == NULL)
		return (1);
	j = 0;
	*i = x;
	while (map_struct->str[*i])
		map_struct->map_array[j++] = ft_strdup(map_struct->str[(*i)++]);
	map_struct->map_array[j] = NULL;
	return 0;
}

int check_all(t_map *map_struct)
{
	if (map_struct->NO == NULL || map_struct->SO == NULL || map_struct->WE == NULL || map_struct->EA == NULL)
		return (ft_putstrn_fd("Error: Invalid map", 2), 1);
	int i = 0;
	while (i < 3)
	{
		if (map_struct->F[i] < 0 || map_struct->F[i] > 255 || map_struct->C[i] < 0 || map_struct->C[i] > 255)
			return (ft_putstrn_fd("Error: Invalid map", 2), 1);
		i++;
	}
	if (map_struct->map_array == NULL)
		return (ft_putstrn_fd("Error: Invalid map", 2), 1);
	return 0;
}

int start_parsing(t_map *map_struct, int ac, char **av)
{
	int i = 0;

	if (ac != 2 || (ac == 2 && av[1] && !check_path(av[1], ft_strlen(av[1]))))
		return (ft_putstrn_fd("Error: Invalid arg", 2), 1);
	if (read_file(map_struct, av) == 1)
		return (1);
	if (read_path(map_struct, &i) == 1)
		return (1);
	if (read_color(map_struct, &i) == 1)
		return (1);
	if (read_map(map_struct, &i) == 1)
		return (1);
	if (check_all(map_struct) == 1)
		return (1);
    return 0;
}