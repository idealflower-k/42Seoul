#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H


void		stack_init(t_stack *stack);
void		stack_push(t_stack *stack, void *value);
void		*stack_pop(t_stack *stack);
void		*stack_peek(t_stack *stack);
void		stack_destory(t_stack *stack);
t_bool		stack_is_empty(t_stack *stack);


void		tree_init(t_tree *tree);
t_tree_node	*create_node(void *value);
void		insert(t_tree_node *node, t_tree_edge edge, t_tree_node *child);
void		pre_order_traversal(t_tree_node *node, void (*f)(t_tree_node*));
void		delete_node(t_tree_node *node);
void		destroy(t_tree *tree);


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