/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:20:39 by kadam             #+#    #+#             */
/*   Updated: 2024/11/11 11:13:13 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_av_path(char *str, int len, int index)
{
	int	fd;

	if (index == 0)
	{
		if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c'
			&& str[len - 4] == '.')
			return (1);
	}
	else if (index == 1)
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
			return (ft_putstrn_fd("Error\nInvalid path\n", 2), 1);
		close(fd);
	}
	return (0);
}

int	process_path(char **str, int i, char *name, char **path)
{
	char	**split;

	split = ft_split(str[i], " \t\v\f\r");
	if (ft_lenarray(split) != 2 || (split[0] && ft_strcmp(split[0], name) != 0))
		return (free_2d_array(split),
			ft_putstrn_fd("Error\nYOU HAVE TO SET ALL THE PATHS\n", 2), 1);
	if (check_av_path(split[1], 0, 1) == 1)
		return (free_2d_array(split),1);
	free(*path);
	*path = ft_strdup(split[1]);
	free_2d_array(split);
	return (0);
}

static int is_new_line(char **line, int *fd, char *av, int j)
{
	if (!*line || !line)
		return (ft_putstrn_fd("Error: Failed to read file", 2), 1);
	while (*line)
	{
		if (*line[0] != '\n')
		{
			j = 1;
			break;
		}
		free(*line);
		*line = get_next_line(*fd);
	}
	free(*line);
	if (j == 0)
		return (ft_putstrn_fd("Error: Empty line", 2), 1);
	close(*fd);
	*fd = open(av, O_RDONLY);
	if (*fd == -1)
		return (ft_putstrn_fd("Error: Failed to open file", 2), 1);
	*line = get_next_line(*fd);
	if (!*line)
		return (ft_putstrn_fd("Error: Failed to read file", 2), 1);
	return (0);
}

static int	init_struct(t_data *data_struct, t_helper *helper, int fd, char *av)
{
	data_struct->no = NULL;
	data_struct->so = NULL;
	data_struct->we = NULL;
	data_struct->ea = NULL;
	data_struct->index = 0;
	int i;

	i = 0;
	while (i < 5)
		data_struct->textur[i++] = NULL;
	i = 0;
	while (i < 7)
		data_struct->gun[i++] = NULL;
	i = 0;
	while (i < 3)
	{
		data_struct->f[i] = -1;
		data_struct->c[i] = -1;
		i++;
	}
	helper->res = 0;
	helper->ptr_line = NULL;
	helper->trim_line = NULL;
	data_struct->map = NULL;
	i = 0;
	while (i < 6)
		helper->find[i++] = 0;
	helper->line = get_next_line(fd);
	if (is_new_line(&helper->line, &fd, av, 0))
		return (1);
	return (0);
}

static int	load_img(t_data *map)
{
	map->textur[0] = mlx_load_png(map->no);
	map->textur[1] = mlx_load_png(map->so);
	map->textur[2] = mlx_load_png(map->we);
	map->textur[3] = mlx_load_png(map->ea);
	map->textur[4] = mlx_load_png("./texturs/door.png");
	if (!map->textur[0] || !map->textur[1] || !map->textur[2]
		|| !map->textur[3] || !map->textur[4])
	
	{
		int i = 0;
		while (i < 5)
		{
			if (map->textur[i])
			{
				mlx_delete_texture(map->textur[i]);
				map->textur[i] = NULL;
			}
			i++;
		}
		return (ft_putstrn_fd("Error\nFailed to load textures\n", 2), 1);

	}
	map->gun[0] = mlx_load_png("./bonus/gun/shoo0.png");
    map->gun[1] = mlx_load_png("./bonus/gun/shoo1.png");
    map->gun[2] = mlx_load_png("./bonus/gun/shoo2.png");
    map->gun[3] = mlx_load_png("./bonus/gun/shoo3.png");
    map->gun[4] = mlx_load_png("./bonus/gun/shoo4.png");
    map->gun[5] = mlx_load_png("./bonus/gun/shoo5.png");
    map->gun[6] = mlx_load_png("./bonus/gun/shoo6.png");
	if (!map->gun[0] || !map->gun[1] || !map->gun[2] || !map->gun[3] || !map->gun[4] || !map->gun[5] || !map->gun[6])
	{
		int i = 0;
		while (i < 7)
		{
			if (map->gun[i])
			{
				mlx_delete_texture(map->gun[i]);
				map->gun[i] = NULL;
			}
			i++;
		}
		return (ft_putstrn_fd("Error\nFailed to load gun textures\n", 2), 1);
	}
	return (0);
}

int	check_all(int ac, char **av, t_data *map_struct, int fd)
{
	t_helper	helper;

	if (init_struct(map_struct, &helper, fd, av[1]))
		return (1);
	if (read_file(fd, &helper))
		return (1);
	if (read_map(helper.line, fd, map_struct, helper.ptr_line))
		return (free(helper.ptr_line), 1);
	free(helper.ptr_line);
	ac = 0;
	while (ac < 3)
	{
		if (map_struct->f[ac] < 0 || map_struct->f[ac] > 255
			|| map_struct->c[ac] < 0 || map_struct->c[ac] > 255)
			return (ft_putstrn_fd("Error\nInvalid color\n", 2), 1);
		ac++;
	}
	if (map_struct->map == NULL)
		return (ft_putstrn_fd("Error\n: The map is empty", 2), 1);
	if (load_img(map_struct))
		return (1);
	return (0);
}
