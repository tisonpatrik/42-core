#include "../../include/optimizer.h"

t_operation	get_inverse_a_operation(t_operation op)
{
	if (op == RA)
		return (RRA);
	return (RA);
}

t_operation	get_inverse_b_operation(t_operation op)
{
	if (op == RB)
		return (RRB);
	return (RB);
}

void	copy_operations_to_list(t_list **dst, t_list *src_start, t_list *src_end, 
								t_optimizer_arena *arena)
{
	t_list *current = src_start;
	while (current != src_end)
	{
		t_operation *op_ptr = arena_alloc_operation(arena);
		if (op_ptr)
		{
			*op_ptr = *(t_operation*)current->content;
			add_operation_to_list(dst, *op_ptr);
		}
		current = current->next;
	}
}

bool	search_for_inverse_a(t_operation op, t_list *current, t_list **dst, 
							t_optimizer_arena *arena, bool *has_changed)
{
	t_operation	inv = get_inverse_a_operation(op);
	t_list		*search = current->next;

	while (search != NULL)
	{
		if (is_barrier(*(t_operation*)search->content) ||
			touches_a(*(t_operation*)search->content))
			break;
		if (*(t_operation*)search->content == inv)
		{
			*has_changed = true;
			copy_operations_to_list(dst, current->next, search, arena);
			return (true);
		}
		search = search->next;
	}
	return (false);
}

bool	search_for_inverse_b(t_operation op, t_list *current, t_list **dst, 
							t_optimizer_arena *arena, bool *has_changed)
{
	t_operation	inv = get_inverse_b_operation(op);
	t_list		*search = current->next;

	while (search != NULL)
	{
		if (is_barrier(*(t_operation*)search->content) ||
			touches_b(*(t_operation*)search->content))
			break;
		if (*(t_operation*)search->content == inv)
		{
			*has_changed = true;
			copy_operations_to_list(dst, current->next, search, arena);
			return (true);
		}
		search = search->next;
	}
	return (false);
}
