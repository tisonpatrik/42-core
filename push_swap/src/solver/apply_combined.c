/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_combined.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:10:24 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/solver.h"

/*
 * Applies combined rotations when both stacks need to
 * rotate in the same direction.
 * This function optimizes rotation operations by combining them when possible:
 * - When both costs are positive: uses rotate_ab (RR) for efficiency
 * - When both costs are negative: uses reverse_rotate_ab (RRR) for efficiency
 *
 * Combined rotations reduce the total number of operations by executing
 * rotations on both stacks simultaneously when they have the same direction.
 *
 * @param ps: Sorting state containing the stacks
 * @param a: Pointer to stack A rotation cost (modified during execution)
 * @param b: Pointer to stack B rotation cost (modified during execution)
 */
static void	apply_combined_rotations(t_sorting_state *ps, int *a, int *b)
{
	while (*a > 0 && *b > 0)
	{
		rotate_ab(ps);
		(*a)--;
		(*b)--;
	}
	while (*a < 0 && *b < 0)
	{
		reverse_rotate_ab(ps);
		(*a)++;
		(*b)++;
	}
}

/*
 * Applies individual rotations for remaining costs after combined rotations.
 *
 * This function handles the remaining rotation costs after combined
 * rotations have been applied. It performs individual rotations:
 * - Stack A rotations: rotate_a (RA) or reverse_rotate_a (RRA)
 * - Stack B rotations: rotate_b (RB) or reverse_rotate_b (RRB)
 *
 * Individual rotations are applied when stacks need to rotate
 * in different directions or when one stack needs additional rotations.
 *
 * @param ps: Sorting state containing the stacks

	* @param a: Pointer to remaining stack A rotation cost

	* @param b: Pointer to remaining stack B rotation cost
 */
static void	apply_individual_rotations(t_sorting_state *ps, int *a, int *b)
{
	while (*a > 0)
	{
		rotate_a(ps);
		(*a)--;
	}
	while (*a < 0)
	{
		reverse_rotate_a(ps);
		(*a)++;
	}
	while (*b > 0)
	{
		rotate_b(ps);
		(*b)--;
	}
	while (*b < 0)
	{
		reverse_rotate_b(ps);
		(*b)++;
	}
}

/*
 * Applies a position by executing rotations and push operations.
 *
 * This function implements the execution of a selected position:
 * 1. Applies combined rotations for efficiency (RR/RRR)
 * 2. Applies individual rotations for remaining costs
 * 3. Performs the push operation (push_b or push_a)
 *
 * The function optimizes the execution by using combined rotations
 * when both stacks need to rotate in the same direction, reducing
 * the total number of operations.
 *
 * @param ps: Sorting state containing the stacks
 * @param p: Position containing rotation costs and target information
 * @param push_to_b: True to push to stack B, false to push to stack A
 */
void	apply_combined(t_sorting_state *ps, t_position p, bool push_to_b)
{
	int	a;
	int	b;

	a = p.cost_a;
	b = p.cost_b;
	apply_combined_rotations(ps, &a, &b);
	apply_individual_rotations(ps, &a, &b);
	if (push_to_b)
		push_b(ps);
	else
		push_a(ps);
}
