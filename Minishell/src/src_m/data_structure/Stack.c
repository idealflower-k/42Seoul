#include "minishell.h"
#include "defines.h"
#include "data_structure.h"

void	stack_init(t_stack *stack)
{
	stack->arr = NULL;
	stack->size = 0;
	stack->push = stack_push;
	stack->pop = stack_pop;
	stack->peek = stack_peek;
	stack->destory = stack_destory;
	stack->is_empty = stack_is_empty;
}

void	stack_push(t_stack *stack, void *value)
{
	ft_lstadd_front(&stack->arr, ft_lstnew(value));
	stack->size++;
}

void	*stack_pop(t_stack *stack)
{
	void	*value;
	t_list	*tmp;

	value = NULL;
	if (stack && stack->size > 0)
	{
		value = stack->arr->content;
		tmp = stack->arr->next;
		free(stack->arr);
		stack->arr = tmp;
		stack->size--;
	}
	return (value);
}

void	*stack_peek(t_stack *stack)
{
	if (stack->is_empty(stack))
		return (NULL);
	return (stack->arr->content);
}

void	stack_destory(t_stack *stack)
{
	void	*tmp;

	while (stack && stack->size > 0)
	{
		tmp = stack->arr;
		stack->arr = stack->arr->next;
		free(tmp);
		stack->size--;
	}
}
