/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_strategy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:53 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

/*
 * Gets the inverse operation for stack A operations.
 *
 * This function returns the inverse operation for stack A:
 * - RA → RRA (rotate A → reverse rotate A)
 * - RRA → RA (reverse rotate A → rotate A)
 *
 * @param op: Stack A operation to find inverse for
 * @return: Inverse operation that cancels the input operation
 */
static t_operation	get_inverse_a_operation(t_operation op)
{
	if (op == RA)
		return (RRA);
	return (RA);
}

/*
 * Gets the inverse operation for stack B operations.
 *
 * This function returns the inverse operation for stack B:
 * - RB → RRB (rotate B → reverse rotate B)
 * - RRB → RB (reverse rotate B → rotate B)
 *
 * @param op: Stack B operation to find inverse for
 * @return: Inverse operation that cancels the input operation
 */
static t_operation	get_inverse_b_operation(t_operation op)
{
	if (op == RB)
		return (RRB);
	return (RB);
}

/*
 * Copies operations from source list to destination list.
 *
 * This function copies a range of operations from the source
 * list to the destination list, excluding the end operation.
 * It's used to copy operations between cancellation points.
 *
 * @param dst: Destination list to copy operations to
 * @param src_start: Starting position in source list
 * @param src_end: Ending position in source list (exclusive)
 */
static void	copy_operations_to_list(t_list **dst, t_list *src_start,
		t_list *src_end)
{
	t_list	*current;

	current = src_start;
	while (current != src_end)
	{
		add_operation_to_list(dst, *(t_operation *)current->content);
		current = current->next;
	}
}

/*
 * Searches for inverse operations of stack A operations.
 *
 * This function implements the cross-stack cancellation strategy for stack A:
 * 1. Determines the inverse operation for the current operation
 * 2. Searches forward for the inverse operation
 * 3. Stops at barrier operations or operations that touch stack A

	* 4. If inverse found: cancels both ops and copies intermediate ops
 * @param op: Stack A operation to find inverse for
 * @param current: Current position in the operation list
 * @param dst: Destination list for non-cancelled operations
 * @param has_changed: Pointer to flag indicating if cancellation occurred
 * @return: True if inverse was found and cancelled, false otherwise
 */
bool	search_for_inverse_a(t_operation op, t_list *current, t_list **dst,
		bool *has_changed)
{
	t_operation	inv;
	t_list		*search;

	inv = get_inverse_a_operation(op);
	search = current->next;
	while (search != NULL)
	{
		if (is_barrier(*(t_operation *)search->content)
			|| touches_a(*(t_operation *)search->content))
			break ;
		if (*(t_operation *)search->content == inv)
		{
			*has_changed = true;
			copy_operations_to_list(dst, current->next, search);
			return (true);
		}
		search = search->next;
	}
	return (false);
}

/*
 * Searches for inverse operations of stack B operations.
 *
 * This function implements the cross-stack cancellation strategy for stack B:
 * 1. Determines the inverse operation for the current operation
 * 2. Searches forward for the inverse operation
 * 3. Stops at barrier operations or operations that touch stack B

	* 4. If inverse found: cancels both ops and copies intermediate ops
 *
 * @param op: Stack B operation to find inverse for
 * @param current: Current position in the operation list
 * @param dst: Destination list for non-cancelled operations
 * @param has_changed: Pointer to flag indicating if cancellation occurred
 * @return: True if inverse was found and cancelled, false otherwise
 */
bool	search_for_inverse_b(t_operation op, t_list *current, t_list **dst,
		bool *has_changed)
{
	t_operation	inv;
	t_list		*search;

	inv = get_inverse_b_operation(op);
	search = current->next;
	while (search != NULL)
	{
		if (is_barrier(*(t_operation *)search->content)
			|| touches_b(*(t_operation *)search->content))
			break ;
		if (*(t_operation *)search->content == inv)
		{
			*has_changed = true;
			copy_operations_to_list(dst, current->next, search);
			return (true);
		}
		search = search->next;
	}
	return (false);
}
