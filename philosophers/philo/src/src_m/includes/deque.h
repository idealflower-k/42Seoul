/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:25:11 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/31 15:52:22 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

t_deque		*deque_init(size_t size);
void		dq_push_front(t_deque *dque, void *data);
void		dq_push_rear(t_deque *dque, void *data);
void		*dq_pop_front(t_deque *dque);
void		*dq_pop_rear(t_deque *dque);
void		*dq_peek_front(const t_deque *dque);
void		*dq_peek_rear(const t_deque *dque);
void		dq_free(const t_deque *dque);
void		dq_clear(t_deque *dque);

#endif