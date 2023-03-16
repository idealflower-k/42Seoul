/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_coord_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:04:53 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/15 16:55:44 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	move_center(t_meta *meta, t_img *img, t_coord **coords)
{
	const int	move_x = (img->width / 2 - \
		coords[meta->map->height / 2][meta->map->width / 2].x);
	const int	move_y = (img->height / 2 - \
		coords[meta->map->height / 2][meta->map->width / 2].y);
	int			x;
	int			y;

	y = 0;
	while (y < meta->map->height)
	{
		x = 0;
		while (x < meta->map->width)
		{
			coords[y][x].x += move_x;
			coords[y][x].y += move_y;
			x++;
		}
		y++;
	}
}