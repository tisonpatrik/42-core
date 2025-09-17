
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
	t_list	*current = src;
	bool	has_changed = false;
	
	while (current != NULL)
	{
		if (current->next != NULL && 
			is_inverse(*(t_operation*)current->content, 
					  *(t_operation*)current->next->content))
		{
			has_changed = true;
			current = current->next->next;
		}
		else
		{
			add_operation_to_list(&dst, *(t_operation*)current->content);
			current = current->next;
		}
	}
	
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

t_list	*cancel_across_other_stack_a(t_list *src, bool *changed)
{
	t_optimizer_arena	*arena;
	t_list				*dst;
	t_list				*current;
	bool				has_changed;

	if (!src || ft_lstsize(src) < 3)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	arena = create_optimizer_arena(ft_lstsize(src));
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	dst = NULL;
	current = src;
	has_changed = false;
	while (current != NULL)
	{
		t_operation	op = *(t_operation*)current->content;
		process_operation_a(op, current, &dst, arena, &has_changed, &current);
		current = current->next;
	}
	if (changed)
		*changed = has_changed;
	destroy_optimizer_arena(arena);
	return (dst);
}

void	process_operation_b(t_operation op, t_list *current, t_list **dst,
							t_optimizer_arena *arena, bool *has_changed, t_list **current_ptr)
{
	if (op == RB || op == RRB)
	{
		if (search_for_inverse_b(op, current, dst, arena, has_changed))
		{
			*current_ptr = current;
			return;
		}
	}
	add_operation_to_list(dst, op);
}

t_list	*cancel_across_other_stack_b(t_list *src, bool *changed)
{
	t_optimizer_arena	*arena;
	t_list				*dst;
	t_list				*current;
	bool				has_changed;

	if (!src || ft_lstsize(src) < 3)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	arena = create_optimizer_arena(ft_lstsize(src));
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	dst = NULL;
	current = src;
	has_changed = false;
	while (current != NULL)
	{
		t_operation	op = *(t_operation*)current->content;
		process_operation_b(op, current, &dst, arena, &has_changed, &current);
		current = current->next;
	}
	if (changed)
		*changed = has_changed;
	destroy_optimizer_arena(arena);
	return (dst);
}
