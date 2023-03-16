/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:20:47 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/15 15:08:50 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(t_meta *meta)
{
	map_scaling(meta->map->coords, meta->map);
	rotation(meta->map, meta);
	move_center(meta, &meta->img, meta->map->coords);
	draw_line(meta->map->coords, &meta->img, meta->map);
}
