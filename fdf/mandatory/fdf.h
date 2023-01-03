/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:50:37 by sanghwal          #+#    #+#             */
/*   Updated: 2023/01/03 21:09:29 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include<fcntl.h>
# include<stdlib.h>
# include<math.h>
# include<stdio.h>

# define PI 3.14159265
# define GREEN 0x000FF000
# define BLUE 0x000000FF
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_Z 6
# define KEY_X 7

typedef struct s_angle
{
	double	x;
	double	y;
	double	z;
}	t_angle;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bit_p_p;
	int		len;
	int		endian;
	int		width;
	int		height;
	t_angle angles;
}	t_img;

typedef struct s_var
{
	void	*mlx;
	void	*win;
}	t_var;


typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
}	t_coord;

typedef struct s_map
{
	void	*map;
	int		width;
	int		height;
	int		scale_size;
	t_coord	**coords;
}	t_map;

typedef struct s_meta
{
	t_var	vars;
	t_map	*map;
	t_img	img;
}	t_meta;

typedef struct s_draw
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	e2;
	int	x[2];
	int	y[2];
	int	z[2];
}	t_draw;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	my_mlx_init(t_meta *meta);
void	draw_line(t_coord **coords, t_img *img, t_map *map);
void	draw_width(t_coord **coords, t_img *img, t_map *map);
void	draw_height(t_coord **coords, t_img *img, t_map *map);
void	draw(t_img *img, t_coord *coord0, t_coord *coord1);
t_draw	*set_draw(t_coord *coord0, t_coord *coord1);

void	rotation_y(t_map *map, double angle);
void	rotation_x(t_map *map, double angle);
void	rotation_z(t_map *map, double angle);
void	rotation_img(int keycode, t_meta *meta);
void	memset_img_data(t_meta *meta, t_img *img);
void	test(t_coord *coord);
void	move_test(t_coord *coord);

int		key_hook(int keycode, t_meta *meta);

t_map	*map_pars(char *file);
char	**read_map(char *file, t_map *map);
void	set_height(char *file, t_map *map);
void	set_width(char *str, t_map *map);
void	set_coords(t_map *map, char **tmp);
int		*matrix1(t_coord *coord);
void	map_scaling(t_coord **coord, t_map *map);
void	move_center(t_meta * meta, t_img *img, t_coord **coords);
void	scaling(t_coord *coord, t_map *map);

void	print_coord(int y, int x, t_coord *coord);
void	*ft_malloc(size_t size);
void	free_double_arr(char **arr);
#endif