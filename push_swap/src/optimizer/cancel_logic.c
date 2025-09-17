#include "../../include/optimizer.h"

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
	setup_cancel_arena_a(src, &arena, &dst, &has_changed);
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	current = src;
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

void	setup_cancel_arena_b(t_list *src, t_optimizer_arena **arena, t_list **dst, bool *has_changed)
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
	setup_cancel_arena_b(src, &arena, &dst, &has_changed);
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	current = src;
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
