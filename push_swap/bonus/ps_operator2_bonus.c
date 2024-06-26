#include "push_swap_bonus.h"

void	op_ra(t_deque *stack_a)
{
	if (stack_a->use_size >= 2)
		dq_push_rear(stack_a, dq_pop_front(stack_a));
	return ;
}

void	op_rb(t_deque *stack_b)
{
	if (stack_b->use_size >= 2)
		dq_push_rear(stack_b, dq_pop_front(stack_b));
	return ;
}

void	op_rr(t_deque *stack_a, t_deque *stack_b)
{
	op_ra(stack_a);
	op_rb(stack_b);
	return ;
}
