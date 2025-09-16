/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_neighbors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:37:36 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
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
			
			if ((a == RA && b == RB) || (a == RB && b == RA))
			{
				t_operation *rr = malloc(sizeof(t_operation));
				if (rr)
				{
					*rr = RR;
					ft_lstadd_back(&dst, ft_lstnew(rr));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			// (rra rrb) -> rrr  and vice versa
			if ((a == RRA && b == RRB) || (a == RRB && b == RRA))
			{
				t_operation *rrr = malloc(sizeof(t_operation));
				if (rrr)
				{
					*rrr = RRR;
					ft_lstadd_back(&dst, ft_lstnew(rrr));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			// (sa sb) -> ss  and vice versa
			if ((a == SA && b == SB) || (a == SB && b == SA))
			{
				t_operation *ss = malloc(sizeof(t_operation));
				if (ss)
				{
					*ss = SS;
					ft_lstadd_back(&dst, ft_lstnew(ss));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			
			// Absorption: rr + rra -> rb ; rr + rrb -> ra
			if (a == RR && b == RRA)
			{
				t_operation *rb = malloc(sizeof(t_operation));
				if (rb)
				{
					*rb = RB;
					ft_lstadd_back(&dst, ft_lstnew(rb));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			if (a == RR && b == RRB)
			{
				t_operation *ra = malloc(sizeof(t_operation));
				if (ra)
				{
					*ra = RA;
					ft_lstadd_back(&dst, ft_lstnew(ra));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			// vice versa
			if (a == RRA && b == RR)
			{
				t_operation *rrb = malloc(sizeof(t_operation));
				if (rrb)
				{
					*rrb = RRB;
					ft_lstadd_back(&dst, ft_lstnew(rrb));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			if (a == RRB && b == RR)
			{
				t_operation *rra = malloc(sizeof(t_operation));
				if (rra)
				{
					*rra = RRA;
					ft_lstadd_back(&dst, ft_lstnew(rra));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			
			// Absorption: rrr + ra -> rrb ; rrr + rb -> rra
			if (a == RRR && b == RA)
			{
				t_operation *rrb = malloc(sizeof(t_operation));
				if (rrb)
				{
					*rrb = RRB;
					ft_lstadd_back(&dst, ft_lstnew(rrb));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			if (a == RRR && b == RB)
			{
				t_operation *rra = malloc(sizeof(t_operation));
				if (rra)
				{
					*rra = RRA;
					ft_lstadd_back(&dst, ft_lstnew(rra));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			// vice versa
			if (a == RA && b == RRR)
			{
				t_operation *rb = malloc(sizeof(t_operation));
				if (rb)
				{
					*rb = RB;
					ft_lstadd_back(&dst, ft_lstnew(rb));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
			if (a == RB && b == RRR)
			{
				t_operation *ra = malloc(sizeof(t_operation));
				if (ra)
				{
					*ra = RA;
					ft_lstadd_back(&dst, ft_lstnew(ra));
				}
				current = current->next->next;
				has_changed = true;
				continue;
			}
		}
		t_operation *op = malloc(sizeof(t_operation));
		if (op)
		{
			*op = *(t_operation*)current->content;
			ft_lstadd_back(&dst, ft_lstnew(op));
		}
		current = current->next;
	}
	
	if (changed)
		*changed = has_changed;
	return (dst);
}
