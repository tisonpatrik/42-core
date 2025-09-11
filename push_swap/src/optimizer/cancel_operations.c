#include "../../include/optimizer.h"

/**
 * Check if two operations are inverse of each other
 * @param a First operation
 * @param b Second operation
 * @return true if operations cancel each other out
 */
bool	is_inverse(t_operation a, t_operation b)
{
	switch (a)
	{
		case RA:
			return (b == RRA);
		case RRA:
			return (b == RA);
		case RB:
			return (b == RRB);
		case RRB:
			return (b == RB);
		case RR:
			return (b == RRR);
		case RRR:
			return (b == RR);
		case SA:
			return (b == SA); // sa;sa -> ∅
		case SB:
			return (b == SB); // sb;sb -> ∅
		case SS:
			return (b == SS); // ss;ss -> ∅
		case PA:
			return (b == PB);
		case PB:
			return (b == PA);
		default:
			return (false);
	}
}

/**
 * Cancel adjacent inverse pairs in the operation sequence
 * @param src Source operation list
 * @return New list with inverse pairs removed (always returns a copy)
 */
t_list	*cancel_inverse_pairs(t_list *src)
{
	if (!src || ft_lstsize(src) < 2)
		return (list_copy(src));
	
	t_list	*dst = NULL;
	t_list	*current = src;
	
	while (current != NULL)
	{
		if (current->next != NULL && 
			is_inverse(*(t_operation*)current->content, 
					  *(t_operation*)current->next->content))
		{
			// Skip both operations (they cancel out)
			current = current->next->next;
		}
		else
		{
			// Add operation to result
			t_operation *op = malloc(sizeof(t_operation));
			if (op == NULL)
			{
				ft_lstclear(&dst, free);
				return (NULL);
			}
			*op = *(t_operation*)current->content;
			ft_lstadd_back(&dst, ft_lstnew(op));
			current = current->next;
		}
	}
	
	return (dst);
}

/**
 * Cancel inverses across other stack for A operations
 * @param src Source operation list
 * @return New list with cross-stack cancellations applied (always returns a copy)
 */
t_list	*cancel_across_other_stack_a(t_list *src)
{
	if (!src || ft_lstsize(src) < 3)
		return (list_copy(src));
	
	t_list	*dst = NULL;
	t_list	*current = src;
	
	while (current != NULL)
	{
		t_operation op = *(t_operation*)current->content;
		if (op == RA || op == RRA)
		{
			t_operation inv = (op == RA) ? RRA : RA;
			t_list	*search = current->next;
			
			while (search != NULL)
			{
				if (is_barrier(*(t_operation*)search->content) ||
					touches_a(*(t_operation*)search->content))
					break;
				if (*(t_operation*)search->content == inv)
				{
					// Add B-only operations between them
					t_list	*temp = current->next;
					while (temp != search)
					{
						t_operation *op_copy = malloc(sizeof(t_operation));
						if (op_copy == NULL)
						{
							ft_lstclear(&dst, free);
							return (NULL);
						}
						*op_copy = *(t_operation*)temp->content;
						ft_lstadd_back(&dst, ft_lstnew(op_copy));
						temp = temp->next;
					}
					current = search;
					goto next;
				}
				search = search->next;
			}
		}
		// Add current operation
		t_operation *op_copy = malloc(sizeof(t_operation));
		if (op_copy == NULL)
		{
			ft_lstclear(&dst, free);
			return (NULL);
		}
		*op_copy = op;
		ft_lstadd_back(&dst, ft_lstnew(op_copy));
	next:
		current = current->next;
	}
	
	return (dst);
}

/**
 * Cancel inverses across other stack for B operations
 * @param src Source operation list
 * @return New list with cross-stack cancellations applied (always returns a copy)
 */
t_list	*cancel_across_other_stack_b(t_list *src)
{
	if (!src || ft_lstsize(src) < 3)
		return (list_copy(src));
	
	t_list	*dst = NULL;
	t_list	*current = src;
	
	while (current != NULL)
	{
		t_operation op = *(t_operation*)current->content;
		if (op == RB || op == RRB)
		{
			t_operation inv = (op == RB) ? RRB : RB;
			t_list	*search = current->next;
			
			while (search != NULL)
			{
				if (is_barrier(*(t_operation*)search->content) ||
					touches_b(*(t_operation*)search->content))
					break;
				if (*(t_operation*)search->content == inv)
				{
					// Add A-only operations between them
					t_list	*temp = current->next;
					while (temp != search)
					{
						t_operation *op_copy = malloc(sizeof(t_operation));
						if (op_copy == NULL)
						{
							ft_lstclear(&dst, free);
							return (NULL);
						}
						*op_copy = *(t_operation*)temp->content;
						ft_lstadd_back(&dst, ft_lstnew(op_copy));
						temp = temp->next;
					}
					current = search;
					goto next;
				}
				search = search->next;
			}
		}
		// Add current operation
		t_operation *op_copy = malloc(sizeof(t_operation));
		if (op_copy == NULL)
		{
			ft_lstclear(&dst, free);
			return (NULL);
		}
		*op_copy = op;
		ft_lstadd_back(&dst, ft_lstnew(op_copy));
	next:
		current = current->next;
	}
	
	return (dst);
}
