/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:00:20 by sanghwal          #+#    #+#             */
/*   Updated: 2023/04/06 16:23:43 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef DINING_H
# define DINING_H

t_bool	set_dining(t_info *info);
t_bool	init_philo(t_info *info);
t_bool	init_philo_data(t_philo *philo, t_info *info, int id);
void	init_info(t_info *info);
t_bool	init_forks(void);

#endif