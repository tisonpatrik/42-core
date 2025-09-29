/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:33:17 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 21:46:10 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"

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

static void	initialize_lis_tracking_for_position(t_lis_computation *computation,
		int current_position)
{
	computation->lis_lengths[current_position] = 1;
	computation->previous_indices[current_position] = -1;
}

/*
 * Computes the longest increasing subsequence
 *
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
void	compute_longest_lens(t_lis_computation *computation,
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
