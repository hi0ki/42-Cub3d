/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:20:39 by kadam             #+#    #+#             */
/*   Updated: 2024/10/31 12:49:09 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_av_path(char *str, int len, int index)
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
		return (1);
	free(*path);
	*path = ft_strdup(split[1]);
	free_2d_array(split);
	return (0);
}

static int	init_struct(t_data *data_struct, t_helper *helper, int fd, int i)
{
	map_struct->no = NULL;
	map_struct->so = NULL;
	map_struct->we = NULL;
	map_struct->ea = NULL;
	i = 0;
	while (i < 3)
	{
		map_struct->f[i] = -1;
		map_struct->c[i] = -1;
		i++;
	}
	helper->res = 0;
	helper->ptr_line = NULL;
	helper->trim_line = NULL;
	i = 0;
	while (i < 6)
		helper->find[i++] = 0;
	helper->line = get_next_line(fd);
	if (!helper->line)
		return (ft_putstrn_fd("Error: Failed to read file", 2), 1);
	return (0);
}

static int	load_img(t_data *data)
{
	datatextur[0] = mlx_load_png(datano);
	datatextur[1] = mlx_load_png(dataso);
	datatextur[2] = mlx_load_png(datawe);
	datatextur[3] = mlx_load_png(dataea);
	if (!datatextur[0] || !datatextur[1] || !datatextur[2]
		|| !datatextur[3])
		return (ft_putstrn_fd("Error\nUnable to load texture\n", 2), 1);
	return (0);
}

int	check_all(int ac, char **av, t_data *data_struct, int fd)
{
	t_helper	helper;

	if (ac != 2 || (ac == 2 && av[1] && !check_av_path(av[1], ft_strlen(av[1]),
				0)))
		return (ft_putstrn_fd("Error\nInvalid arg\n", 2), 1);
	if (init_struct(map_struct, &helper, fd, 0))
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
