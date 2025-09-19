/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_neighbors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:24 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 22:40:12 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

bool	try_merge_operations(t_merge_context *ctx)
{
	if (try_merge_rotate_pairs(ctx))
		return (true);
	if (try_merge_swap_pairs(ctx))
		return (true);
	if (try_merge_absorption_cases(ctx))
		return (true);
	return (false);
}

void	process_operation_pair(t_list **dst, t_list **current,
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

t_list	*process_operation_list(t_list *src, bool *has_changed)
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
