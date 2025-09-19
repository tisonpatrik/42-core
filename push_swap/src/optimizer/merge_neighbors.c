/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_neighbors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:24 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 21:28:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

t_list	*merge_neighbors(t_list *src, bool *changed)
{
	t_list				*dst;
	bool				has_changed;
	t_list				*current;
	t_operation			a;
	t_operation			b;
	t_merge_context		ctx;

	if (!src || ft_lstsize(src) < 2)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	dst = NULL;
	has_changed = false;
	current = src;
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			a = *(t_operation *)current->content;
			b = *(t_operation *)current->next->content;
			ctx.a = a;
			ctx.b = b;
			ctx.dst = &dst;
			ctx.current = &current;
			if (try_merge_operations(&ctx))
			{
				has_changed = true;
				continue ;
			}
		}
		add_operation_to_list(&dst, *(t_operation *)current->content);
		current = current->next;
	}
	if (changed)
		*changed = has_changed;
	return (dst);
}
