#include "push_swap.h"

void	op_sa(t_deque *stack_a, t_oper *op_lst, int flag)
{
	int	tmp1;
	int	tmp2;

	tmp1 = 0;
	tmp2 = 0;
	if (stack_a->use_size >= 2)
	{
		tmp1 = dq_pop_front(stack_a);
		tmp2 = dq_pop_front(stack_a);
		dq_push_front(stack_a, tmp1);
		dq_push_front(stack_a, tmp2);
		if (flag == 1 && op_lst != 0)
			add_op(op_lst, "sa");
	}
	return ;
}

void	op_sb(t_deque *stack_b, t_oper *op_lst, int flag)
{
	int	tmp1;
	int	tmp2;

	tmp1 = 0;
	tmp2 = 0;
	if (stack_b->use_size >= 2)
	{
		tmp1 = dq_pop_front(stack_b);
		tmp2 = dq_pop_front(stack_b);
		dq_push_front(stack_b, tmp1);
		dq_push_front(stack_b, tmp2);
		if (flag == 1 && op_lst != 0)
			add_op(op_lst, "sb");
	}
	return ;
}

void	op_ss(t_deque *stack_a, t_deque *stack_b, t_oper *op_lst)
{
	op_sa(stack_a, op_lst, 0);
	op_sb(stack_b, op_lst, 0);
	if (op_lst != 0)
		add_op(op_lst, "ss");
	return ;
}

void	op_pa(t_deque *stack_a, t_deque *stack_b, t_oper *op_lst)
{
	if (stack_b->use_size > 0)
	{
		dq_push_front(stack_a, dq_pop_front(stack_b));
		if (op_lst != 0)
			add_op(op_lst, "pa");
	}
	return ;
}

void	op_pb(t_deque *stack_a, t_deque *stack_b, t_oper *op_lst)
{
	if (stack_a->use_size > 0)
	{
		dq_push_front(stack_b, dq_pop_front(stack_a));
		if (op_lst != 0)
			add_op(op_lst, "pb");
	}
	return ;
}
