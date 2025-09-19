/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_neighbors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:24 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 20:49:26 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

t_list	*merge_neighbors(t_list *src, bool *changed)
{
	t_list		*dst;
	bool		has_changed;
	t_list		*current;
	t_operation	a;
	t_operation	b;

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
			if (try_merge_operations(a, b, &dst, &current))
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
