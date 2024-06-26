#include "push_swap.h"

void	make_hourglass(t_deque *s_a, t_deque *s_b, t_oper *op_lst)
{
	size_t			i;
	const size_t	chunk = set_chunk(s_a->capacity);

	i = 0;
	while (i < s_a->capacity)
	{
		if (get_front(s_a) <= i)
		{
			op_pb(s_a, s_b, op_lst);
			i++;
		}
		else if (get_front(s_a) > i && get_front(s_a) <= i + chunk)
		{
			op_pb(s_a, s_b, op_lst);
			i++;
			op_rb(s_b, op_lst, 1);
		}
		else if (get_front(s_a) > i + chunk)
			check_rra(s_a, op_lst, i + chunk);
	}
}

void	check_rra(t_deque *s_a, t_oper *op_lst, size_t ichunk)
{
	if (!(get_rear(s_a) > ichunk))
		op_rra(s_a, op_lst, 1);
	else if ((get_rear(s_a) > ichunk))
		op_ra(s_a, op_lst, 1);
}

size_t	get_front(t_deque *stack)
{
	return (stack->nodes[stack->front].idx);
}

size_t	get_rear(t_deque *stack)
{
	return (stack->nodes[stack->rear].idx);
}
