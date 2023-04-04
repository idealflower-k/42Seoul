/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:53:11 by sanghwal          #+#    #+#             */
/*   Updated: 2023/04/04 16:26:30 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREAD_H
# define PHILO_THREAD_H

void	*start_routine(void *arg);
t_bool	init_forks(void);
t_bool	init_philo(t_info *info);
t_bool	init_philo_data(t_philo *philo, t_info *info, int id);
void	init_info(t_info *info);
t_bool	create_thread(pthread_t *threads);
t_bool	save_state_message(t_philo *philo, char *state);

#endif