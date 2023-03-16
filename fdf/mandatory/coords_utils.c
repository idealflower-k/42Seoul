/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:14:54 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/15 15:47:12 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	copy_coords(t_map *map, t_coord **og_coords)
{
	int	y;
	int	x;

	map->coords = (t_coord **)ft_malloc((sizeof(t_coord *) * map->height));
	y = 0;
	while (y < map->height)
	{
		x = 0;
		map->coords[y] = (t_coord *)ft_malloc((sizeof(t_coord) * \
				map->width));
		while (x < map->width)
		{
			map->coords[y][x].y = og_coords[y][x].y;
			map->coords[y][x].x = og_coords[y][x].x;
			map->coords[y][x].z = og_coords[y][x].z;
			x++;
		}
		y++;
	}
}

void	get_og_coords(t_map *map, t_coord **coords, t_coord **og_coords)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			coords[y][x].x = og_coords[y][x].x;
			coords[y][x].y = og_coords[y][x].y;
			coords[y][x].z = og_coords[y][x].z;
			x++;
		}
		y++;
	}
}

void	scaling(t_coord *og_coord, t_coord *coord, t_map *map)
{
	coord->x = map->scale_size * og_coord->x;
	coord->y = map->scale_size * og_coord->y;
	coord->z = 3 * og_coord->z;
}
