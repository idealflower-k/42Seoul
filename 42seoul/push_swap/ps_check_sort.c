/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:53:59 by sanghwal          #+#    #+#             */
/*   Updated: 2022/11/04 19:15:15 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
int	check_sort(t_deque *stack)
{
	size_t	i;

	i = 0;
	while (i < stack->use_size)
	{
		if (i == stack->nodes[i].idx)
			i++;
		else
			return (0);
	}
	return (1);
}
