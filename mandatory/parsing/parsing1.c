/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:20:39 by kadam             #+#    #+#             */
/*   Updated: 2024/11/10 21:21:17 by kadam            ###   ########.fr       */
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
		return (free_2d_array(split), 1);
	free(*path);
	*path = ft_strdup(split[1]);
	free_2d_array(split);
	return (0);
}

static int	load_img(t_data *data)
{
	int	i;

	data->textur[0] = mlx_load_png(data->no);
	data->textur[1] = mlx_load_png(data->so);
	data->textur[2] = mlx_load_png(data->we);
	data->textur[3] = mlx_load_png(data->ea);
	if (!data->textur[0] || !data->textur[1] || !data->textur[2]
		|| !data->textur[3])
	{
		i = 0;
		while (i < 4)
		{
			if (data->textur[i])
			{
				mlx_delete_texture(data->textur[i]);
				data->textur[i] = NULL;
			}
			i++;
		}
		return (ft_putstrn_fd("Error\nUnable to load texture\n", 2), 1);
	}
	return (0);
}

int	check_all(int ac, char **av, t_data *data_struct, int fd)
{
	t_helper	helper;

	if (init_struct(data_struct, &helper, fd, av[1]))
		return (1);
	if (read_file(fd, &helper))
		return (1);
	if (read_map(helper.line, fd, data_struct, helper.ptr_line))
		return (free(helper.ptr_line), free(helper.line), 1);
	free(helper.ptr_line);
	ac = 0;
	while (ac < 3)
	{
		if (data_struct->f[ac] < 0 || data_struct->f[ac] > 255
			|| data_struct->c[ac] < 0 || data_struct->c[ac] > 255)
			return (ft_putstrn_fd("Error\nInvalid color\n", 2), 1);
		ac++;
	}
	if (data_struct->map == NULL)
		return (ft_putstrn_fd("Error\n: The map is empty", 2), 1);
	if (load_img(data_struct))
		return (1);
	return (0);
}
