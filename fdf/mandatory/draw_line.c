/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:37:39 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/13 19:48:51 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_coord **coords, t_img *img, t_map *map)
{
	draw_width(coords, img, map);
	draw_height(coords, img, map);
}

void	draw_width(t_coord **coords, t_img *img, t_map *map)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	color = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width - 1)
		{
			if (map->og_coords[y][x].z == 0)
				color = BLUE;
			if (map->og_coords[y][x].z > 0 || map->og_coords[y][x + 1].z > 0)
				color = RED;
			else
				color = GREEN;
			draw(img, &coords[y][x], &coords[y][x + 1], color);
			x++;
		}
		y++;
	}
}

void	draw_height(t_coord **coords, t_img *img, t_map *map)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height - 1)
		{
			if (map->og_coords[y][x].z == 0)
				color = BLUE;
			if (map->og_coords[y][x].z > 0 || map->og_coords[y + 1][x].z > 0)
				color = RED;
			else
				color = GREEN;
			draw(img, &coords[y][x], &coords[y + 1][x], color);
			y++;
		}
		x++;
	}
}

void	draw(t_img *img, t_coord *coord0, t_coord *coord1, int color)
{
	t_draw	*draw;

	draw = set_draw(coord0, coord1);
	while (draw)
	{
		my_mlx_pixel_put(img, draw->x[0], draw->y[0], color);
		if (draw->x[0] == draw->x[1] && draw->y[0] == draw->y[1])
			break ;
		draw->e2 = 2 * draw->error;
		if (draw->e2 >= draw->dy)
		{
			if (draw->x[0] == draw->x[1])
				break ;
			draw->error += draw->dy;
			draw->x[0] += draw->sx;
		}
		else if (draw->e2 <= draw->dx)
		{
			if (draw->y[0] == draw->y[1])
				break ;
			draw->error += draw->dx;
			draw->y[0] += draw->sy;
		}
	}
	free(draw);
}

t_draw	*set_draw(t_coord *coord0, t_coord *coord1)
{
	t_draw	*draw;

	if (!coord0 || !coord1)
		return (0);
	draw = ft_malloc(sizeof(t_draw));
	draw->x[0] = coord0->x;
	draw->x[1] = coord1->x;
	draw->y[0] = coord0->y;
	draw->y[1] = coord1->y;
	draw->z[0] = coord0->z;
	draw->z[1] = coord1->z;
	draw->dx = abs(coord1->x - coord0->x);
	draw->dy = -abs(coord1->y - coord0->y);
	draw->error = draw->dx + draw->dy;
	draw->sx = 1;
	draw->sy = 1;
	if (coord1->x < coord0->x)
		draw->sx = -1;
	if (coord1->y < coord0->y)
		draw->sy = -1;
	return (draw);
}

void	get_color(t_coord *og_coords, int *color)
{
	if (og_coords->z == 0)
				*color = BLUE;
			if (og_coords.z > 0 || (og_coords + 1).z > 0)
				*color = RED;
			else
				*color = GREEN;
}