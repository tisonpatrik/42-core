#include "../../include/optimizer.h"

bool	is_inverse(t_operation a, t_operation b)
{
	if (a == RA)
		return (b == RRA);
	if (a == RRA)
		return (b == RA);
	if (a == RB)
		return (b == RRB);
	if (a == RRB)
		return (b == RB);
	if (a == RR)
		return (b == RRR);
	if (a == RRR)
		return (b == RR);
	if (a == SA)
		return (b == SA);
	if (a == SB)
		return (b == SB);
	if (a == SS)
		return (b == SS);
	if (a == PA)
		return (b == PB);
	if (a == PB)
		return (b == PA);
	return (false);
}

void	process_inverse_cancellation(t_list *src, t_list **dst, bool *has_changed)
{
	t_list	*current = src;
	
	while (current != NULL)
	{
		if (current->next != NULL && 
			is_inverse(*(t_operation*)current->content, 
					  *(t_operation*)current->next->content))
		{
			*has_changed = true;
			current = current->next->next;
		}
		else
		{
			add_operation_to_list(dst, *(t_operation*)current->content);
			current = current->next;
		}
	}
}

t_list	*cancel_inverse_pairs(t_list *src, bool *changed)
{
	if (!src || ft_lstsize(src) < 2)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	
	t_optimizer_arena *arena = create_optimizer_arena(ft_lstsize(src));
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	
	t_list	*dst = NULL;
	bool	has_changed = false;
	
	process_inverse_cancellation(src, &dst, &has_changed);
	
	if (changed)
		*changed = has_changed;
	
	destroy_optimizer_arena(arena);
	return (dst);
}

void	process_operation_a(t_operation op, t_list *current, t_list **dst,
							t_optimizer_arena *arena, bool *has_changed, t_list **current_ptr)
{
	if (op == RA || op == RRA)
	{
		if (search_for_inverse_a(op, current, dst, arena, has_changed))
		{
			*current_ptr = current;
			return;
		}
	}
	add_operation_to_list(dst, op);
}

void	setup_cancel_arena_a(t_list *src, t_optimizer_arena **arena, t_list **dst, bool *has_changed)
{
	*arena = create_optimizer_arena(ft_lstsize(src));
	if (!*arena)
	{
		*has_changed = false;
		return;
	}
	*dst = NULL;
	*has_changed = false;
}
