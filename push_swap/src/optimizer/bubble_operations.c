#include "../../include/optimizer.h"

/**
 * Copy a list of operations
 * @param src Source list
 * @return New list with copied operations
 */
t_list	*list_copy(t_list *src)
{
	t_list	*dst = NULL;
	t_list	*current = src;
	
	while (current != NULL)
	{
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
	return (dst);
}

/**
 * Get operation at specific index in list
 * @param list List to search
 * @param index Index to get
 * @return Operation at index, or NULL if not found
 */
t_operation	get_operation_at_index(t_list *list, int index)
{
	t_list	*current = list;
	int		i = 0;
	
	while (current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	
	if (current == NULL)
		return (SA); // Default fallback
	return (*(t_operation*)current->content);
}

/**
 * Set operation at specific index in list
 * @param list List to modify
 * @param index Index to set
 * @param op Operation to set
 */
void	set_operation_at_index(t_list *list, int index, t_operation op)
{
	t_list	*current = list;
	int		i = 0;
	
	while (current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	
	if (current != NULL)
		*(t_operation*)current->content = op;
}

/**
 * Helper function: attempt to bubble op at index j through [i+1..j-1]
 * @param out List to modify
 * @param i Start index
 * @param j End index
 * @param is_a Whether we're bubbling an A operation
 * @return true if bubbling was successful
 */
bool	bubble_operation(t_list *out, int i, int j, bool is_a)
{
	// Allow only "other stack only" in gap and no barriers
	for (int k = i + 1; k < j; k++)
	{
		t_operation op_k = get_operation_at_index(out, k);
		if (is_barrier(op_k))
			return (false);
		// When bubbling A-op, gap must be B-only
		if (is_a && (touches_a(op_k) || (!touches_b(op_k) && !is_pure_b(op_k))))
			return (false);
		// When bubbling B-op, gap must be A-only
		if (!is_a && (touches_b(op_k) || (!touches_a(op_k) && !is_pure_a(op_k))))
			return (false);
	}
	// Perform series of adjacent swaps (commutation)
	for (int k = j; k > i + 1; k--)
	{
		t_operation temp = get_operation_at_index(out, k);
		set_operation_at_index(out, k, get_operation_at_index(out, k - 1));
		set_operation_at_index(out, k - 1, temp);
	}
	return (true);
}

/**
 * Bubble operation across other stack operations
 * @param src Source operation list
 * @param max_gap Maximum gap for bubbling
 * @return New list with bubbled operations (always returns a copy)
 */
t_list	*bubble_across_other_stack(t_list *src, int max_gap)
{
	if (!src)
		return (src);
	int		n = ft_lstsize(src);
	if (n < 3)
		return (list_copy(src));
	
	t_list	*out = list_copy(src);
	if (out == NULL)
		return (NULL);
	
	// Go through sequence and look for pairs to merge within maxGap range
	for (int i = 0; i < n - 1; i++)
	{
		t_operation a = get_operation_at_index(out, i);
		
		// A-op + look for suitable B-op in window to create rr/rrr
		if (a == RA || a == RRA)
		{
			t_operation want = (a == RA) ? RB : RRB;
			for (int j = i + 1; j < n && j - i - 1 <= max_gap; j++)
			{
				t_operation op_j = get_operation_at_index(out, j);
				if (op_j == want)
				{
					if (bubble_operation(out, i, j, true)) // bubble B-op through B-only block
					{
						// Move one step further, merge will handle next pass
					}
					break;
				}
				if (is_barrier(op_j) || touches_a(op_j))
					break; // Hit barrier or A-op → not this way
			}
			continue;
		}
		
		// B-op + look for suitable A-op in window
		if (a == RB || a == RRB)
		{
			t_operation want = (a == RB) ? RA : RRA;
			for (int j = i + 1; j < n && j - i - 1 <= max_gap; j++)
			{
				t_operation op_j = get_operation_at_index(out, j);
				if (op_j == want)
				{
					if (bubble_operation(out, i, j, false)) // bubble A-op through A-only block
					{
						// Bubbling successful
					}
					break;
				}
				if (is_barrier(op_j) || touches_b(op_j))
					break;
			}
			continue;
		}
	}
	
	return (out);
}
