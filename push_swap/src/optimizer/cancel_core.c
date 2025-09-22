/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:50:05 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

/*
 * Checks if two operations are inverse (cancel each other out).
 *
 * This function determines whether two operations cancel each other
 * when applied in sequence. Inverse operations include:
 * - RA ↔ RRA (rotate A ↔ reverse rotate A)
 * - RB ↔ RRB (rotate B ↔ reverse rotate B)
 * - RR ↔ RRR (rotate both ↔ reverse rotate both)
 * - SA ↔ SA (swap A cancels itself)
 * - SB ↔ SB (swap B cancels itself)
 * - SS ↔ SS (swap both cancels itself)
 * - PA ↔ PB (push A to B ↔ push B to A)
 *
 * @param a: First operation
 * @param b: Second operation
 * @return: True if operations are inverse, false otherwise
 */
static bool	is_inverse(t_operation a, t_operation b)
{
	if (a == RA)
		return (b == RRA);
	if (a == RRA)
		return (b == RA);
	if (a == RB)
		return (b == RRB);
	if (a == RRB)
		return (b == RB);
	if (a == RR)
		return (b == RRR);
	if (a == RRR)
		return (b == RR);
	if (a == SA)
		return (b == SA);
	if (a == SB)
		return (b == SB);
	if (a == SS)
		return (b == SS);
	if (a == PA)
		return (b == PB);
	if (a == PB)
		return (b == PA);
	return (false);
}

/*
 * Processes the source list to cancel adjacent inverse operation pairs.
 *
 * This function implements the inverse pair cancellation algorithm:
 * 1. Iterates through the source list
 * 2. Checks each pair of adjacent operations
 * 3. If operations are inverse: skips both operations
 * 4. If operations are not inverse: adds the first operation to result
 *
 * @param src: Source operation list to process
 * @param dst: Destination list for non-cancelled operations
 * @param has_changed: Pointer to flag indicating if cancellations occurred
 */
static void	process_inverse_cancellation(t_list *src, t_list **dst,
		bool *has_changed)
{
	t_list	*current;

	current = src;
	while (current != NULL)
	{
		if (current->next != NULL
			&& is_inverse(*(t_operation *)current->content,
				*(t_operation *)current->next->content))
		{
			*has_changed = true;
			current = current->next->next;
		}
		else
		{
			add_operation_to_list(dst, *(t_operation *)current->content);
			current = current->next;
		}
	}
}

/*
 * Cancels adjacent inverse operation pairs in the sequence.
 *
 * This function implements the inverse pair cancellation strategy:
 * 1. Validates input sequence (requires at least 2 operations)
 * 2. Processes the sequence to find and cancel inverse pairs
 * 3. Returns optimized sequence with cancelled operations removed
 *
 * @param src: Source operation sequence to optimize
 * @param changed: Pointer to flag indicating if changes were made
 * @return: Optimized operation sequence with cancelled pairs removed
 */
t_list	*cancel_inverse_pairs(t_list *src, bool *changed)
{
	t_list				*dst;
	bool				has_changed;

	if (!src || ft_lstsize(src) < 2)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	dst = NULL;
	has_changed = false;
	process_inverse_cancellation(src, &dst, &has_changed);
	if (changed)
		*changed = has_changed;
	return (dst);
}
