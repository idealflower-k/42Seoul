/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:42:50 by sanghwal          #+#    #+#             */
/*   Updated: 2022/11/04 19:25:56 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	main(int ac, char *av[])
{
	t_split	*head;
	t_deque	*stack_a;
	int		i;

	if (ac < 2)
		exit(0);
	i = 1;
	head = 0;
	while (av[i] != 0)
	{
		if (av[i][0] == '\0')
			handle_error(1);
		head = split_num(av[i++], head);
	}
	stack_a = deque_creat(head->len);
	if (!stack_a)
		handle_error(1);
	fill_stack_a(stack_a, head);
	set_checker(stack_a);
}

void	set_checker(t_deque *stack_a)
{
	t_deque	*stack_b;
	int		*cp_stack;

	stack_b = deque_creat(stack_a->capacity);
	cp_stack = (int *)malloc(sizeof(int) * stack_a->capacity);
	if (!stack_b || !cp_stack)
		handle_error(1);
	sort_copy(copy_stack(stack_a, cp_stack), stack_a->capacity);
	indexing_stack(cp_stack, stack_a);
	checker(stack_a, stack_b);
}

void	checker(t_deque *s_a, t_deque *s_b)
{
	char	*cmd;

	cmd = get_next_line(0);
	while (cmd)
	{
		ft_printf("%s\n", cmd);
		do_op(s_a, s_b, cmd);
		for (size_t i = 0; i < s_a->use_size; i++)
		{
			size_t idx = 0;
			printf("stack idx : %zu\n", s_a->nodes[idx].idx);
			if (idx == s_a->capacity-1)
				idx = 0;
		}
		cmd = get_next_line(0);
	}
	if (s_b->use_size == 0 && check_sort(s_a))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	exit(0);
}

void	do_op(t_deque *s_a, t_deque *s_b, char *cmd)
{
	if (ft_strncmp(cmd, "sa\n", 3) == 0)
		op_sa(s_a, 0, 0);
	else if (ft_strncmp(cmd, "sb\n", 3) == 0)
		op_sb(s_b, 0, 0);
	else if (ft_strncmp(cmd, "ss\n", 3) == 0)
		op_ss(s_a, s_b, 0);
	else if (ft_strncmp(cmd, "pa\n", 3) == 0)
		op_pa(s_a, s_b, 0);
	else if (ft_strncmp(cmd, "pb\n", 3) == 0)
		op_pb(s_a, s_b, 0);
	else if (ft_strncmp(cmd, "ra\n", 3) == 0)
		op_ra(s_a, 0, 0);
	else if (ft_strncmp(cmd, "rb\n", 3) == 0)
		op_rb(s_b, 0, 0);
	else if (ft_strncmp(cmd, "rr\n", 3) == 0)
		op_rr(s_a, s_b, 0);
	else if (ft_strncmp(cmd, "rra\n", 4) == 0)
		op_rra(s_a, 0, 0);
	else if (ft_strncmp(cmd, "rrb\n", 4) == 0)
		op_rrb(s_b, 0, 0);
	else if (ft_strncmp(cmd, "rrr\n", 4) == 0)
		op_rrr(s_a, s_b, 0);
	else
		handle_error(1);
}

t_split	*split_num(char *av, t_split *head)
{
	char	**splited;

	if (!head)
		head = lst_creat();
	splited = ft_split(av, ' ');
	if (!splited || splited[0] == 0)
		handle_error(1);
	put_lst(head, splited);
	return (head);
}
