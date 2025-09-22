/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:39:18 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>

/*
 * Calculates the merged cost for rotating both stacks.
 *
 * This function optimizes the cost calculation by considering whether
 * both stacks can be rotated in the same direction simultaneously.
 * The algorithm:
 * - If both rotations have the same sign (both positive or both negative),
 *   the cost is the maximum of the two absolute values
 * - If rotations have different signs, the cost is the sum of both
 *
 * This optimization reduces the total number of operations needed
 * when both stacks need to be rotated in the same direction.
 *
 * @param a: Cost for rotating stack A (can be negative)
 * @param b: Cost for rotating stack B (can be negative)
 * @return: Optimized merged cost
 */
int	merged_cost(int a, int b)
{
	int		cost_a;
	int		cost_b;
	bool	same_sign;

	cost_a = ft_abs(a);
	cost_b = ft_abs(b);
	same_sign = (a > 0 && b > 0) || (a < 0 && b < 0);
	if (same_sign)
	{
		if (cost_a > cost_b)
		{
			return (cost_a);
		}
		return (cost_b);
	}
	return (cost_a + cost_b);
}

/*
 * Calculates the signed cost for rotating a stack to a specific position.
 *
 * This function determines the most efficient way to rotate a stack
 * to bring an element at a given index to the top. The algorithm:
 * - If index <= size/2: rotate forward (positive cost)
 * - If index > size/2: rotate backward (negative cost)
 *
 * The negative cost indicates that reverse rotation (rr) is more
 * efficient than forward rotation (r) for that position.
 *
 * @param idx: Index of the element to bring to top (0-based)
 * @param size: Total size of the stack
 * @return: Signed cost (positive for forward, negative for backward)
 */
int	signed_cost(int idx, int size)
{
	if (idx <= size / 2)
		return (idx);
	return (idx - size);
}

/*
 * Compares two positions to determine which is better.
 *
 * This function implements a hierarchical comparison for positions:
 * 1. Total cost: Lower total cost is preferred
 * 2. Absolute cost A: Lower absolute cost for stack A rotations
 * 3. Target index: Lower target index (closer to top)
 * 4. Source index: Lower source index (closer to top)
 *
 * This ensures deterministic ordering when positions have equal costs,
 * preferring moves that involve elements closer to the top of stacks.
 *
 * @param a: First position to compare
 * @param b: Second position to compare
 * @return: True if position a is better than position b
 */
bool	is_better_position(t_position a, t_position b)
{
	if (a.total != b.total)
		return (a.total < b.total);
	if (ft_abs(a.cost_a) != ft_abs(b.cost_a))
		return (ft_abs(a.cost_a) < ft_abs(b.cost_a));
	if (a.to_index != b.to_index)
		return (a.to_index < b.to_index);
	return (a.from_index < b.from_index);
}
