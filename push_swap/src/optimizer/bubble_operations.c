/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:50:41 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:11 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

/*
 * Sets an operation at a specific index in the list.
 *
 * This function traverses the list to find the node at the
 * specified index and updates its content with the new operation.
 * If the index is out of bounds, the function does nothing.
 *
 * @param list: List to modify
 * @param index: Index of the operation to set
 * @param op: New operation to set at the index
 */
void	set_operation_at_index(t_list *list, int index, t_operation op)
{
	t_list	*current;
	int		i;

	current = list;
	i = 0;
	while (current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	if (current != NULL)
		*(t_operation *)current->content = op;
}

/*
 * Checks if an operation can be bubbled to a target position.
 *
 * This function validates whether an operation can be moved
 * from position i to position j without violating constraints:
 * 1. Checks for barrier operations in the path
 * 2. Ensures no conflicting operations are in the way
 * 3. Validates stack-specific constraints
 *
 * @param out: List containing the operations
 * @param i: Source position of the operation
 * @param j: Target position for the operation
 * @param is_a: True if operation affects stack A, false for stack B
 * @return: True if operation can be bubbled, false otherwise
 */
static bool	can_bubble_operation(t_list *out, int i, int j, bool is_a)
{
	t_operation	op_k;
	int			k;

	k = i + 1;
	while (k < j)
	{
		op_k = get_operation_at_index(out, k);
		if (is_barrier(op_k))
			return (false);
		if (is_a && (touches_a(op_k) || (!touches_b(op_k) && !is_pure_b(op_k))))
			return (false);
		if (!is_a && (touches_b(op_k) || (!touches_a(op_k)
					&& !is_pure_a(op_k))))
			return (false);
		k++;
	}
	return (true);
}

/*
 * Bubbles an operation from position i to position j.
 *
 * This function implements the bubble operation algorithm:
 * 1. Validates that the operation can be bubbled
 * 2. Swaps the operation with adjacent operations
 * 3. Moves the operation step by step to the target position
 *
 * The bubbling process helps reorder operations for better
 * optimization opportunities.
 *
 * @param out: List containing the operations
 * @param i: Source position of the operation
 * @param j: Target position for the operation
 * @param is_a: True if operation affects stack A, false for stack B
 * @return: True if operation was successfully bubbled, false otherwise
 */
bool	bubble_operation(t_list *out, int i, int j, bool is_a)
{
	t_operation	temp;
	int			k;

	if (!can_bubble_operation(out, i, j, is_a))
		return (false);
	k = j;
	while (k > i + 1)
	{
		temp = get_operation_at_index(out, k);
		set_operation_at_index(out, k, get_operation_at_index(out, k - 1));
		set_operation_at_index(out, k - 1, temp);
		k--;
	}
	return (true);
}
