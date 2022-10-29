/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:50:16 by sanghwal          #+#    #+#             */
/*   Updated: 2022/10/29 17:44:16 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sorting(t_deque *stack_a)
{
	t_deque	*stack_b;
	t_oper	*op_lst;
	int		*sorted;
	int		*cp_stack;

	stack_b = deque_creat(stack_a->capacity);
	sorted = (int *)malloc(sizeof(int) * stack_a->capacity);
	cp_stack = (int *)malloc(sizeof(int) * stack_a->capacity);
	if (!stack_b || !sorted || !cp_stack)
		handle_error(1);
	sort_copy(copy_stack(stack_a, cp_stack));
	indexing_stack(cp_stack, stack_a);
	op_lst = 0;
	op_lst = do_sort(stack_a, stack_b);
}

t_oper	*do_sort(t_deque *stack_a, t_deque *stack_b)
{
	t_oper	*op_lst;

	stack_b = 0;
	op_lst = 0;
	add_op(op_lst, 0);
	hourglass_sort(stack_a, stack_b, op_lst);
	return (op_lst);
}

t_oper	*add_op(t_oper *op_lst, char *op)
{
	t_oper	*tmp;
	t_oper	*new;

	if (op == 0)
	{
		op_lst = (t_oper *)malloc(sizeof(t_oper));
		if (!op_lst)
			handle_error(0);
		op_lst->next = 0;
		op_lst->op = 0;
		return (op_lst);
	}
	else
	{
		tmp = op_lst;
		while (tmp->next != 0)
			tmp = tmp->next;
		new = (t_oper *)malloc(sizeof(t_oper));
		if (!new)
			handle_error(0);
		tmp->next = new;
		new->next = 0;
		new->op = op;
	}
	return (op_lst);
}

size_t	set_chunk(size_t capacity)
{
	size_t	chunk;

	chunk = (size_t)(0.000000053 * (capacity * capacity) \
		+ 0.03 * (capacity) + 14.5);
	printf("chunk = %zu\n", chunk);
	return (chunk);
}

void	hourglass_sort(t_deque *s_a, t_deque *s_b, t_oper *op_lst)
{
	make_hourglass(s_a, s_b, op_lst);
	make_sorted_a(s_a, s_b, op_lst);
}

void	make_hourglass(t_deque *s_a, t_deque *s_b, t_oper *op_lst)
{
	const size_t	chunk = set_chunk(s_a->capacity);
	size_t			cnt;
	size_t			i;

	i = 0;
	cnt = s_a->capacity;
	while (cnt != 0)
	{
		if (s_a->nodes[s_a->front].data <= i)
		{
			op_pb(s_a, s_b, op_lst);
			i++;
		}
		else if (s_a->nodes[s_a->front].data < i \
			&& s_a->nodes[s_a->front].data <= i + chunk)
		{
			op_pb(s_a, s_b, op_lst);
			op_rb(s_a, op_lst, 1);
			i++;
		}
		else if (s_a->nodes[s_a->front].data > i + chunk)
		{
			if (i < s_a->capacity / 2 && i >= 0)
				op_rra(s_a, op_lst, 1);
			else
				op_ra(s_a, op_lst, 1);
		}
		cnt--;
	}
}
