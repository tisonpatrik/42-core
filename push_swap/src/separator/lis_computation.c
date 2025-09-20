/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_computation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:25:30 by ptison            #+#    #+#             */
/*   Updated: 2025/09/20 17:05:13 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include <stdbool.h>

/*
 * Updates the best LIS result if the current position provides a longer
 * subsequence.
 *
 * This function is called during the dynamic programming computation to track
 * the longest increasing subsequence found so far.
 *
 * @param computation: The LIS computation state
 * @param best_result: Pointer to the current best result
 * @param current_position: The position being evaluated
 */
static void	update_best_lis_if_improved(t_lis_computation *computation,
		t_lis_result *best_result, int current_position)
{
	if (computation->lis_lengths[current_position] >= best_result->best_len)
	{
		best_result->best_len = computation->lis_lengths[current_position];
		best_result->best_end = current_position;
	}
}

/*
 * Attempts to extend the LIS from a previous element to the current element.
 *
 * This implements the core logic of the dynamic programming LIS algorithm:
 * - Condition 1: values[previous] < values[current] (increasing sequence)
 * - Condition 2: lis_lengths[previous] + 1 > lis_lengths[current] (better
 * length)
 *
 * If both conditions are met, updates the current position to extend from
 * the previous element, creating a longer increasing subsequence.
 *
 * @param computation: The LIS computation state
 * @param current: The current position being evaluated
 * @param previous: The previous position to potentially extend from
 */
static void	try_extend_lis_from_previous_element(t_lis_computation *computation,
		int current, int previous)
{
	if (computation->values[previous] < computation->values[current]
		&& computation->lis_lengths[previous]
		+ 1 > computation->lis_lengths[current])
	{
		computation->lis_lengths[current] = computation->lis_lengths[previous]
			+ 1;
		computation->previous_indices[current] = previous;
	}
}

/*
 * Initializes LIS tracking for a specific position.
 *
 * Each position starts with LIS length 1 (itself) and no previous element.
 * This is the base case for the dynamic programming algorithm.
 *
 * @param computation: The LIS computation state
 * @param current_position: The position to initialize
 */
void	initialize_lis_tracking_for_position(t_lis_computation *computation,
		int current_position)
{
	computation->lis_lengths[current_position] = 1;
	computation->previous_indices[current_position] = -1;
}

/*
 * Computes the longest increasing subsequence using dynamic programming.
 *
 * This is the core LIS algorithm with O(n²) time complexity:
 * 1. For each position i from 0 to n-1:
 *    - Initialize LIS[i] = 1, prev[i] = -1
 *    - For each position j from 0 to i-1:
 *      - If values[j] < values[i] and LIS[j] + 1 > LIS[i]:
 *        - Update LIS[i] = LIS[j] + 1, prev[i] = j
 *    - Update best result if LIS[i] is better
 *
 * The algorithm builds the LIS by considering each element and determining
 * the longest increasing subsequence ending at that position.
 *
 * @param computation: The LIS computation state containing values and tracking
 * arrays
 * @param best_result: Pointer to store the best LIS result
 */
void	compute_longest_increasing_lens(t_lis_computation *computation,
		t_lis_result *best_result)
{
	int	current_position;
	int	previous_position;

	best_result->best_len = 0;
	best_result->best_end = 0;
	current_position = 0;
	while (current_position < computation->n)
	{
		initialize_lis_tracking_for_position(computation, current_position);
		previous_position = 0;
		while (previous_position < current_position)
		{
			try_extend_lis_from_previous_element(computation, current_position,
				previous_position);
			previous_position++;
		}
		update_best_lis_if_improved(computation, best_result, current_position);
		current_position++;
	}
}

t_node	**get_lis_nodes(t_stack *stack, t_separator_arena *arena)
{
	int				stack_size;
	t_lis_result	result;

	stack_size = get_size(stack);
	if (stack_size <= 0)
	{
		if (!arena->lis_nodes)
			return (NULL);
		return (arena->lis_nodes);
	}
	extract_stack_values_to_computation(stack, arena->computation);
	compute_longest_increasing_lens(arena->computation, &result);
	return (build_lis_result(arena->computation, &result, arena));
}
