/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_neighbors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:37:36 by patrik            #+#    #+#             */
/*   Updated: 2025/09/17 22:56:36 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

static void	*copy_operation(void *content)
{
	t_operation *op = malloc(sizeof(t_operation));
	if (op)
		*op = *(t_operation*)content;
	return (op);
}


static void	add_operation_to_list(t_list **dst, t_operation op)
{
	t_operation *op_ptr = malloc(sizeof(t_operation));
	if (op_ptr)
	{
		*op_ptr = op;
		ft_lstadd_back(dst, ft_lstnew(op_ptr));
	}
}

static bool	try_merge_operations(t_operation a, t_operation b, t_list **dst, t_list **current)
{
	// (ra rb) -> rr and vice versa
	if ((a == RA && b == RB) || (a == RB && b == RA))
	{
		add_operation_to_list(dst, RR);
		*current = (*current)->next->next;
		return (true);
	}
	// (rra rrb) -> rrr and vice versa
	if ((a == RRA && b == RRB) || (a == RRB && b == RRA))
	{
		add_operation_to_list(dst, RRR);
		*current = (*current)->next->next;
		return (true);
	}
	// (sa sb) -> ss and vice versa
	if ((a == SA && b == SB) || (a == SB && b == SA))
	{
		add_operation_to_list(dst, SS);
		*current = (*current)->next->next;
		return (true);
	}
	// Absorption: rr + rra -> rb ; rr + rrb -> ra
	if ((a == RR && b == RRA) || (a == RRA && b == RR))
	{
		add_operation_to_list(dst, (a == RR) ? RB : RRB);
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RR && b == RRB) || (a == RRB && b == RR))
	{
		add_operation_to_list(dst, (a == RR) ? RA : RRA);
		*current = (*current)->next->next;
		return (true);
	}
	// Absorption: rrr + ra -> rrb ; rrr + rb -> rra
	if ((a == RRR && b == RA) || (a == RA && b == RRR))
	{
		add_operation_to_list(dst, (a == RRR) ? RRB : RB);
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RRR && b == RB) || (a == RB && b == RRR))
	{
		add_operation_to_list(dst, (a == RRR) ? RRA : RA);
		*current = (*current)->next->next;
		return (true);
	}
	return (false);
}

t_list	*merge_neighbors(t_list *src, bool *changed)
{
	if (!src || ft_lstsize(src) < 2)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	
	t_list	*dst = NULL;
	bool	has_changed = false;
	t_list	*current = src;
	
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			t_operation a = *(t_operation*)current->content;
			t_operation b = *(t_operation*)current->next->content;
			
			if (try_merge_operations(a, b, &dst, &current))
			{
				has_changed = true;
				continue;
			}
		}
		add_operation_to_list(&dst, *(t_operation*)current->content);
		current = current->next;
	}
	
	if (changed)
		*changed = has_changed;
	
	return (dst);
}
