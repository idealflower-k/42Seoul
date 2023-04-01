/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:53:54 by sanghwal          #+#    #+#             */
/*   Updated: 2023/04/01 20:48:54 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "defines.h"
#include "meta.h"
#include "philo_thread.h"
#include "utils.h"

t_bool	create_thread(pthread_t *threads)
{
	t_philo		*philos;
	const int	num = get_args()->num_philo;
	int			i;

	philos = get_philos();
	i = 0;
	while (i < num)
	{
		if (pthread_create(&threads[i], NULL, start_routine, &philos[i]))
		{
			set_err(ERR_PTHREAD_CREATE);
			detach_threads(threads, i);
			return (FT_FALSE);
		}
		i++;
	}
}
