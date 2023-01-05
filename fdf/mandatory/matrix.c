/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:47:34 by sanghwal          #+#    #+#             */
/*   Updated: 2023/01/05 13:53:08 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*matrix1(t_coord *coord)
{
	int	*mr1;

	mr1 = ft_malloc(sizeof(int) * 3);
	mr1[0] = coord->x;
	mr1[1] = coord->y;
	mr1[2] = coord->z;
	return (mr1);
}
