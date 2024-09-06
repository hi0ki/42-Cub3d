// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   start_parsing.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/09/04 16:25:05 by kadam             #+#    #+#             */
// /*   Updated: 2024/09/05 17:48:31 by kadam            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../include/cub3d.h"

int check_av(char *str, int len)
{
    if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c' && str[len - 4] == '.')
        return (1);
    return (0);
}

int check_path(char *str)
{
    int fd = open(str, O_RDONLY);
    if (fd == -1)
        return (ft_putstrn_fd("Error: Invalid path", 2), 1);
    close(fd);
    return (0);
}

int process_path(char **str, int i, char *name, char **path)
{
    char **split = ft_split(str[i], " \t\v\f\r");
    if (ft_lenarray(split) != 2 || (split[0] && ft_strcmp(split[0], name) != 0))
        return (free_2d_array(split), ft_putstrn_fd("Error: Invalid map", 2), 1);
    // if (check_path(split[1]) == 1)
    // 	return 1;
    free(*path);
    *path = ft_strdup(split[1]);
    free_2d_array(split);
    return 0;
}

int process_color(int *map_color, char *str, char *name)
{
    char **split = ft_split(str, "  \t\v\f\r");
    if (ft_lenarray(split) < 2 || (split[0] && ft_strcmp(split[0], name) != 0))
        return (free_2d_array(split), ft_putstrn_fd("Error: Invalid map", 2), 1);
    char *tmp = NULL;
    char *ptr = NULL;
    int i = 1;
    while (split[i])
    {
        tmp = ft_strjoin(ptr, split[i]);
        free(ptr);
        ptr = tmp;
        i++;
    }
    free_2d_array(split);
    i = 0;
    int commas = 0;
    while (ptr[i])
    {
        if (ptr[i] == ',' && ptr[i + 1] != ',' && ptr[i + 1] != '\0' && ptr[i - 1] && ptr[i - 1] != ',')
            commas++;
        else if (ptr[i] == ',' && (ptr[i + 1] == ',' || ptr[i + 1] == '\0' || (ptr[i - 1] && ptr[i - 1] == ',')))
            return (free(ptr), ft_putstrn_fd("Error: Invalid map", 2), 1);
        i++;
    }
    if (commas != 2)
        return (free(ptr), ft_putstrn_fd("Error: Invalid map", 2), 1);
    i = 0;
    while (ptr[i])
    {
        if (ptr[i] != ',' && (ptr[i] < '0' || ptr[i] > '9'))
            return (free(ptr), ft_putstrn_fd("Error: Invalid map", 2), 1);
        i++;
    }
    split = ft_split(ptr, ",");
    free(ptr);
    i = 0;
    while (i < 3)
    {
        map_color[i] = ft_atoi(split[i]);
        i++;
    }
    return (free_2d_array(split), 0);
}

int read_path_color(t_map *map_struct, char **str)
{
    int i = 0;
    while (str[i] && i <= 5)
    {
        if (str[i][0] == 'N')
        {
            if (process_path(str, i, "NO", &(map_struct->NO)))
                return 1;
        }
        else if (str[i][0] == 'S')
        {
            if (process_path(str, i, "SO", &(map_struct->SO)))
                return 1;
        }
        else if (str[i][0] == 'W')
        {
            if (process_path(str, i, "WE", &(map_struct->WE)))
                return 1;
        }
        else if (str[i][0] == 'E')
        {
            if (process_path(str, i, "EA", &(map_struct->EA)))
                return 1;
        }
        else if (str[i][0] == 'F')
        {
            if (process_color(map_struct->F, str[i], "F"))
                return 1;
        }
        else if (str[i][0] == 'C')
        {
            if (process_color(map_struct->C, str[i], "C"))
                return 1;
        }
        i++;
    }
    return 0;
}

void init_struct(t_map *map_struct)
{
    map_struct->NO = NULL;
    map_struct->SO = NULL;
    map_struct->WE = NULL;
    map_struct->EA = NULL;
    for (int i = 0; i < 3; i++)
    {
        map_struct->F[i] = -1;
        map_struct->C[i] = -1;
    }
}
int check_is_new_line(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

int process_line(char c, char *line, char **ptr_line, int *find)
{
    if (c == 'N')
        find[0]++;
    else if (c == 'S')
        find[1]++;
    else if (c == 'W')
        find[2]++;
    else if (c == 'E')
        find[3]++;
    else if (c == 'F')
        find[4]++;
    else if (c == 'C')
        find[5]++;
    else
    {
        int x = 0;
        while (x < 6)
        {
            if (find[x] != 1)
                return (ft_putstrn_fd("Error: Invalid file", 2), 1);
            x++;
        }
        return (0);
    }
    char *trim_line = ft_strtrim(line, " \t\v\f\r");
    char *join_line = ft_strjoin(*ptr_line, trim_line);
    free(trim_line);
    free(*ptr_line);
    *ptr_line = ft_strdup(join_line);
    free(join_line);
    return (2);
}

void print_struct(t_map *map_struct)
{
    printf("NO: %s\n", map_struct->NO);
    printf("SO: %s\n", map_struct->SO);
    printf("WE: %s\n", map_struct->WE);
    printf("EA: %s\n", map_struct->EA);
    printf("F: %d, %d, %d\n", map_struct->F[0], map_struct->F[1], map_struct->F[2]);
    printf("C: %d, %d, %d\n", map_struct->C[0], map_struct->C[1], map_struct->C[2]);
    for (int i = 0; map_struct->map_array[i]; i++)
        printf("%s\n", map_struct->map_array[i]);
}
int read_file_1(t_map *map_struct, int fd)
{
    char *line = get_next_line(fd);
    if (!line)
        return (ft_putstrn_fd("Error: Failed to read file", 2), 1);
    int find[6] = {0, 0, 0, 0, 0, 0};
    int res = 0;
    char *ptr_line = NULL;
    char *trim_line = NULL;
    while (line != NULL)
    {
        trim_line = ft_strtrim(line, " \t\v\f\r");
        if (ft_strcmp(trim_line, "\n") == 0)
        {
            free(trim_line);
            free(line);
            line = get_next_line(fd);
            continue;
        }
        else
        {
            res = process_line(trim_line[0], line, &ptr_line, find);
            free(trim_line);
            if (res == 0)
                break;
            else if (res == 1)
            {
                free(line);
                free(ptr_line);
                return (1);
            }
        }
        free(line);
        line = get_next_line(fd);
    }
    char **str = ft_split(ptr_line, "\n");
    if (read_path_color(map_struct, str))
        return (free_2d_array(str), 1);
    free_2d_array(str);
    free(ptr_line);

    char *tmp = NULL;
    while (line)
    {
        tmp = _strjoin(tmp, line);
        free(line);
        line = get_next_line(fd);
    }
    map_struct->map_array = ft_split(tmp, "\n");
    free(tmp);
    // print_struct(map_struct);
    return (0);
}

int check_all(int ac, char **av, t_map *map_struct, int fd)
{
    if (ac != 2 || (ac == 2 && av[1] && !check_av(av[1], ft_strlen(av[1]))))
        return (ft_putstrn_fd("Error: Invalid arg", 2), 1);
    init_struct(map_struct);
    if (read_file_1(map_struct, fd))
        return (1);
    int i = 0;
    while (i < 3)
    {
        if (map_struct->F[i] < 0 || map_struct->F[i] > 255 || map_struct->C[i] < 0 || map_struct->C[i] > 255)
            return (ft_putstrn_fd("Error: Invalid map", 2), 1);
        i++;
    }
    if (map_struct->map_array == NULL)
        return (ft_putstrn_fd("Error: Invalid map", 2), 1);
    return (0);
}