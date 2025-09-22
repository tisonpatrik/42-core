/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_neighbors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:24 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

static bool	try_merge_operations(t_merge_context *ctx)
{
	if (try_merge_rotate_pairs(ctx))
		return (true);
	if (try_merge_swap_pairs(ctx))
		return (true);
	if (try_merge_absorption_cases(ctx))
		return (true);
	return (false);
}

static void	process_operation_pair(t_list **dst, t_list **current,
		bool *has_changed)
{
	t_operation		a;
	t_operation		b;
	t_merge_context	ctx;

	a = *(t_operation *)(*current)->content;
	b = *(t_operation *)(*current)->next->content;
	ctx.a = a;
	ctx.b = b;
	ctx.dst = dst;
	ctx.current = current;
	if (try_merge_operations(&ctx))
	{
		*has_changed = true;
		return ;
	}
	add_operation_to_list(dst, *(t_operation *)(*current)->content);
	*current = (*current)->next;
}

static t_list	*process_operation_list(t_list *src, bool *has_changed)
{
	t_list	*dst;
	t_list	*current;

	dst = NULL;
	*has_changed = false;
	current = src;
	while (current != NULL)
	{
		if (current->next != NULL)
			process_operation_pair(&dst, &current, has_changed);
		else
		{
			add_operation_to_list(&dst, *(t_operation *)current->content);
			current = current->next;
		}
	}
	return (dst);
}

/*
 * Merges adjacent operations that can be combined for better efficiency.
 *
 * This function implements the neighbor merging strategy:
 * 1. Processes all adjacent operation pairs
 * 2. Attempts to merge compatible operations
 * 3. Returns optimized sequence with fewer operations
 *
 * The merging process reduces the total number of operations
 * by combining operations that can be executed together.
 *
 * @param src: Source operation sequence to optimize
 * @param changed: Pointer to flag indicating if changes were made
 * @return: Optimized operation sequence with merged operations
 */
t_list	*merge_neighbors(t_list *src, bool *changed)
{
	if (!src || ft_lstsize(src) < 2)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	return (process_operation_list(src, changed));
}
