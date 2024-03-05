#include "minirt.h"
#include "defs.h"
#include "parser.h"

void	objsadd_back(t_obj **objs, t_obj *new)
{
	t_obj	*node;

	if (!new)
		return ;
	if (!*objs)
	{
		*objs = new;
		return ;
	}
	node = *objs;
	while (node->next)
		node = node->next;
	node->next = new;
}

void	objs_clear(t_obj **objs, void (*del)(void *))
{
	t_obj	*obj;

	if (!*objs || !del)
		return ;
	while (*objs)
	{
		obj = (*objs)->next;
		del(*objs);
		*objs = obj;
	}
	*objs = NULL;
}
