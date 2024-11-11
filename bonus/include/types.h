/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:58:48 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/11 17:11:48 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "cub3d.h"

# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define GREY 0x808080FF
# define NEW 0xE0E0E0FF
# define FOV 1.047198
# define ROTATION_SPEED 0.088
# define MOVE_SPEED 3.0
# define SIZE 20
# define WIDTH 1650
# define HEIGHT 1050

typedef struct s_gun
{
	int				arr[4];
	int				i;
	int				j;
	int				index;
	int				height;
	int				width;
	int				scale_factor;
	int				x_c;
	int				y_c;
	int				k;
	int				l;
}					t_gun;

typedef struct s_helper
{
	int				find[6];
	int				res;
	char			*line;
	char			*ptr_line;
	char			*trim_line;
}					t_helper;

typedef struct s_lines
{
	int				s_x;
	int				e_x;
	int				y;
	int				x_pos;
	struct s_lines	*next;
	struct s_lines	*prv;
}					t_lines;

typedef struct s_player
{
	mlx_image_t		*image_player;
	double			px;
	double			py;
	double			angle;
	int				x;
	int				y;
}					t_player;

typedef struct s_dis_h
{
	double			x_h;
	double			y_h;
	double			dis;
	int				x_o;
	int				y_o;
	bool			close_d;
	bool			open_d;
	char			inter_type_h;
}					t_dis_h;

typedef struct s_dis_v
{
	double			x_v;
	double			y_v;
	double			dis;
	int				x_o;
	int				y_o;
	bool			close_d;
	bool			open_d;
	char			inter_type_v;
}					t_dis_v;

typedef struct s_rays
{
	double			rayangle;
	t_dis_h			dis_h;
	t_dis_v			dis_v;
}					t_rays;

typedef struct s_map
{
	int				f[3];
	int				c[3];
	int				index;
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*textur[5];
	mlx_texture_t	*gun[8];
}					t_data;

#endif