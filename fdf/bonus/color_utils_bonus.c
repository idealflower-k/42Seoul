/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:59:34 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/15 16:55:44 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	set_color_height(t_map *map, int x, int y)
{
	if (map->og_coords[y][x].z == 0)
		map->s_c = WHITE;
	else if (map->og_coords[y][x].z > 0)
		map->s_c = BLUE;
	else if (map->og_coords[y][x].z < 0)
		map->s_c = RED;
	if (map->og_coords[y + 1][x].z == 0)
		map->e_c = WHITE;
	else if (map->og_coords[y + 1][x].z > 0)
		map->e_c = BLUE;
	else if (map->og_coords[y + 1][x].z < 0)
		map->e_c = RED;
}

void	set_color_width(t_map *map, int x, int y)
{
	if (map->og_coords[y][x].z == 0)
		map->s_c = WHITE;
	else if (map->og_coords[y][x].z > 0)
		map->s_c = BLUE;
	else if (map->og_coords[y][x].z < 0)
		map->s_c = RED;
	if (map->og_coords[y][x + 1].z == 0)
		map->e_c = WHITE;
	else if (map->og_coords[y][x + 1].z > 0)
		map->e_c = BLUE;
	else if (map->og_coords[y][x + 1].z < 0)
		map->e_c = RED;
}