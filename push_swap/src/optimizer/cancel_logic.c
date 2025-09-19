/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:58 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 21:04:50 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

t_list	*cancel_across_other_stack_a(t_list *src, bool *changed)
{
	t_optimizer_arena	*arena;
	t_list				*dst;
	t_list				*current;
	bool				has_changed;
	t_operation			op;

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
	has_changed = false;
	current = src;
	while (current != NULL)
	{
		op = *(t_operation *)current->content;
		process_operation_a(op, current, &dst, &has_changed, &current);
		current = current->next;
	}
	if (changed)
		*changed = has_changed;
	destroy_optimizer_arena(arena);
	return (dst);
}

void	process_operation_b(t_operation op, t_list *current, t_list **dst,
		bool *has_changed, t_list **current_ptr)
{
	if (op == RB || op == RRB)
	{
		if (search_for_inverse_b(op, current, dst, has_changed))
		{
			*current_ptr = current;
			return ;
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
	t_operation			op;

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
	has_changed = false;
	current = src;
	while (current != NULL)
	{
		op = *(t_operation *)current->content;
		process_operation_b(op, current, &dst, &has_changed, &current);
		current = current->next;
	}
	if (changed)
		*changed = has_changed;
	destroy_optimizer_arena(arena);
	return (dst);
}
