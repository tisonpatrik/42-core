/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 21:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/09 21:00:00 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Get the absolute value of an integer
 *
 * @param n The integer value
 * @return The absolute value
 */
static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/**
 * @brief Calculate the signed cost to move an element to a specific index
 *
 * This function calculates the optimal rotation cost (positive for rotate,
 * negative for reverse rotate) to move an element at the given index to the
 * top of the stack.
 *
 * @param idx The current index of the element
 * @param size The total size of the stack
 * @return Positive value for rotate operations, negative for reverse rotate
 */
__attribute__((unused))
static int	calculate_signed_cost(int idx, int size)
{
	if (idx <= size / 2)
		return (idx);
	return (idx - size);
}

/**
 * @brief Calculate the total cost when combining two operations
 *
 * This function calculates the merged cost when performing two operations
 * simultaneously, accounting for common rotations (rr/rrr) that can be
 * combined into a single operation.
 *
 * @param cost_a The cost of the first operation
 * @param cost_b The cost of the second operation
 * @return The total cost after accounting for combined operations
 */
__attribute__((unused))
static int	calculate_merged_cost(int cost_a, int cost_b)
{
	int	same_direction;

	same_direction = (cost_a >= 0 && cost_b >= 0) || (cost_a < 0 && cost_b < 0);
	if (same_direction)
	{
		if (ft_abs(cost_a) > ft_abs(cost_b))
			return (ft_abs(cost_a));
		return (ft_abs(cost_b));
	}
	return (ft_abs(cost_a) + ft_abs(cost_b));
}
