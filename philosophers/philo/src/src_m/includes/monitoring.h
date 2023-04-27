/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:24:00 by sanghwal          #+#    #+#             */
/*   Updated: 2023/04/07 15:15:44 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H

void	monitoring(void);
t_bool	display_philo_state(void);
void	print_message(uint64_t elapsed_time, int id, char *state);
t_bool	print_all_message(void);
t_bool	terminate_true(void);
t_bool	check_philo(t_arg *arg);
t_bool	check_die(uint64_t curr_time, t_philo *philo);
t_bool	check_must_eat(t_philo *philo, int *must_cnt);

#endif