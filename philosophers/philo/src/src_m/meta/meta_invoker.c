/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_invoker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:14:22 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/29 17:52:51 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "defines.h"
#include "meta.h"

t_meta	*get_meta(int ac, char **av)
{
	return ((t_meta *)meta_receiver(META, ac, av));
}

pthread_mutex_t	*get_forks(void)
{
	return ((pthread_mutex_t *)meta_receiver(META_FORKS, 0, NULL));
}

pthread_t	*get_philos(void)
{
	return ((pthread_t *)meta_receiver(META_PHILOS, 0, NULL));
}

t_arg	*get_args(void)
{
	return ((t_arg *)meta_receiver(META_ARG, 0, NULL));
}
