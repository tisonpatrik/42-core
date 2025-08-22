#include "models.h"

void	post_sort_optimization(t_ps *data);
void	eliminate_neutral_op(t_list *op_list);
void	merge_op(t_list *op_list);
void	remove_op(t_list *to_delete);
t_op	neutral_op(t_op op);
bool	op_on_same_stack(t_op ref, t_op to_check);
t_op	child_op(t_op first, t_op second);
t_op	op_from(t_list *node);
void	eliminate_neutral_op(t_list *op_list)
{
	t_list	*ref;
	t_list	*cmp;
	t_op	op_neutral;

	ref = op_list->next;
	while (ref && ref->next)
	{
		op_neutral = neutral_op(op_from(ref));
		if (op_neutral)
		{
			cmp = ref->next;
			while (!op_on_same_stack(op_from(ref), op_from(cmp))
				&& op_from(cmp) != op_neutral && cmp->next)
				cmp = cmp->next;
			if (ref->prev && op_from(cmp) == op_neutral)
			{
				ref = ref->prev;
				remove_op(ref->next);
				remove_op(cmp);
				continue ;
			}
		}
		ref = ref->next;
	}
}

void	merge_op(t_list *op_list)
{
	t_list	*reader;
	t_op	child;

	reader = op_list;
	while (reader && reader->next)
	{
		child = child_op(op_from(reader), op_from(reader->next));
		if (child)
		{
			remove_op(reader->next);
			reader->content = (void *)(uintptr_t)child;
		}
		reader = reader->next;
	}
}
void	post_sort_optimization(t_ps *data)
{
	if (!data->op_list)
		return ;
	eliminate_neutral_op(data->op_list);
	merge_op(data->op_list);
}