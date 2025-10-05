/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align_min_to_top.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:01:47 by ptison            #+#    #+#             */
/*   Updated: 2025/10/05 20:31:10 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include "../../include/solver.h"

/*
 * Performs the necessary rotations to align the minimum element to the top.
 *
 * This function executes the rotations based on the calculated cost:
 * - Positive cost: performs forward rotations (RA)
 * - Negative cost: performs reverse rotations (RRA)
 *
 * The cost represents the number of positions the minimum element
 * needs to be moved to reach the top of the stack.
 *
 * @param ps: Sorting state containing the stacks
 * @param cost: Number of rotations needed (positive for forward,
	negative for reverse)
 */
static void	perform_rotations(t_sorting_state *ps, int cost)
{
	while (cost > 0)
	{
		rotate_a(ps);
		cost--;
	}
	while (cost < 0)
	{
		reverse_rotate_a(ps);
		cost++;
	}
}

/*
 * Aligns the minimum element to the top of stack A.
 *
 * This function implements the final alignment step of the push_swap algorithm:
 * 1. Finds the index of the minimum element in stack A
 * 2. Calculates the optimal rotation cost using signed_cost()
 * 3. Performs the necessary rotations to bring the minimum to the top
 *
 * The alignment ensures that the stack is in its final sorted state
 * with the minimum element at the top, completing the sorting process.
 *
 * @param ps: Sorting state containing the stacks
 */
void	align_min_to_top(t_sorting_state *ps)
{
	int	size_a;
	int	min_idx;
	int	cost;

	size_a = get_size(ps->a);
	if (size_a == 0)
		return ;
	min_idx = find_min_index(ps->a);
	cost = signed_cost(min_idx, size_a);
	perform_rotations(ps, cost);
}
