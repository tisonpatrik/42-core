#include "../../include/optimizer.h"

/**
 * Merge neighboring operations that can be combined
 * @param src Source operation list
 * @return New list with merged operations
 */
t_list	*merge_neighbors(t_list *src)
{
	if (!src || ft_lstsize(src) < 2)
		return (src);
	
	t_list	*dst = NULL;
	t_list	*current = src;
	bool	changed = false;
	
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			t_operation a = *(t_operation*)current->content;
			t_operation b = *(t_operation*)current->next->content;
			
			// (ra rb) -> rr and vice versa
			if ((a == RA && b == RB) || (a == RB && b == RA))
			{
				t_operation *rr = malloc(sizeof(t_operation));
				if (rr == NULL)
					return (src);
				*rr = RR;
				ft_lstadd_back(&dst, ft_lstnew(rr));
				current = current->next->next;
				changed = true;
				continue;
			}
			// (rra rrb) -> rrr and vice versa
			if ((a == RRA && b == RRB) || (a == RRB && b == RRA))
			{
				t_operation *rrr = malloc(sizeof(t_operation));
				if (rrr == NULL)
					return (src);
				*rrr = RRR;
				ft_lstadd_back(&dst, ft_lstnew(rrr));
				current = current->next->next;
				changed = true;
				continue;
			}
			// (sa sb) -> ss and vice versa
			if ((a == SA && b == SB) || (a == SB && b == SA))
			{
				t_operation *ss = malloc(sizeof(t_operation));
				if (ss == NULL)
					return (src);
				*ss = SS;
				ft_lstadd_back(&dst, ft_lstnew(ss));
				current = current->next->next;
				changed = true;
				continue;
			}
			
			// Absorption: rr + rra -> rb ; rr + rrb -> ra
			if (a == RR && b == RRA)
			{
				t_operation *rb = malloc(sizeof(t_operation));
				if (rb == NULL)
					return (src);
				*rb = RB;
				ft_lstadd_back(&dst, ft_lstnew(rb));
				current = current->next->next;
				changed = true;
				continue;
			}
			if (a == RR && b == RRB)
			{
				t_operation *ra = malloc(sizeof(t_operation));
				if (ra == NULL)
					return (src);
				*ra = RA;
				ft_lstadd_back(&dst, ft_lstnew(ra));
				current = current->next->next;
				changed = true;
				continue;
			}
			// vice versa
			if (a == RRA && b == RR)
			{
				t_operation *rrb = malloc(sizeof(t_operation));
				if (rrb == NULL)
					return (src);
				*rrb = RRB;
				ft_lstadd_back(&dst, ft_lstnew(rrb));
				current = current->next->next;
				changed = true;
				continue;
			}
			if (a == RRB && b == RR)
			{
				t_operation *rra = malloc(sizeof(t_operation));
				if (rra == NULL)
					return (src);
				*rra = RRA;
				ft_lstadd_back(&dst, ft_lstnew(rra));
				current = current->next->next;
				changed = true;
				continue;
			}
			
			// Absorption: rrr + ra -> rrb ; rrr + rb -> rra
			if (a == RRR && b == RA)
			{
				t_operation *rrb = malloc(sizeof(t_operation));
				if (rrb == NULL)
					return (src);
				*rrb = RRB;
				ft_lstadd_back(&dst, ft_lstnew(rrb));
				current = current->next->next;
				changed = true;
				continue;
			}
			if (a == RRR && b == RB)
			{
				t_operation *rra = malloc(sizeof(t_operation));
				if (rra == NULL)
					return (src);
				*rra = RRA;
				ft_lstadd_back(&dst, ft_lstnew(rra));
				current = current->next->next;
				changed = true;
				continue;
			}
			// vice versa
			if (a == RA && b == RRR)
			{
				t_operation *rb = malloc(sizeof(t_operation));
				if (rb == NULL)
					return (src);
				*rb = RB;
				ft_lstadd_back(&dst, ft_lstnew(rb));
				current = current->next->next;
				changed = true;
				continue;
			}
			if (a == RB && b == RRR)
			{
				t_operation *ra = malloc(sizeof(t_operation));
				if (ra == NULL)
					return (src);
				*ra = RA;
				ft_lstadd_back(&dst, ft_lstnew(ra));
				current = current->next->next;
				changed = true;
				continue;
			}
		}
		// Add current operation
		t_operation *op_copy = malloc(sizeof(t_operation));
		if (op_copy == NULL)
			return (src);
		*op_copy = *(t_operation*)current->content;
		ft_lstadd_back(&dst, ft_lstnew(op_copy));
		current = current->next;
	}
	
	if (changed)
		ft_lstclear(&src, free);
	else
	{
		ft_lstclear(&dst, free);
		return (src);
	}
	
	return (dst);
}
