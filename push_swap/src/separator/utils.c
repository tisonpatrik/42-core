/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:35:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/12 19:16:24 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>

int	extract_stack_values_to_computation(t_stack *stack, t_lis_computation *computation)
{
	t_node	*current_node;
	int		index;

	current_node = get_head(stack);
	index = 0;
	while (index < computation->n)
	{
		computation->nodes[index] = current_node;
		computation->values[index] = get_content(current_node);
		current_node = get_next(current_node);
		index++;
	}
	return (0);
}

void	update_best_lis_if_improved(t_lis_computation *computation,
		t_lis_result *best_result, int current_position)
{
	if (computation->lis_lengths[current_position] >= best_result->best_len)
	{
		best_result->best_len = computation->lis_lengths[current_position];
		best_result->best_end = current_position;
	}
}

void	try_extend_lis_from_previous_element(t_lis_computation *computation,
		int current_position, int previous_position)
{
	if (computation->values[previous_position] < computation->values[current_position]
		&& computation->lis_lengths[previous_position]
		+ 1 > computation->lis_lengths[current_position])
	{
		computation->lis_lengths[current_position] = computation->lis_lengths[previous_position]
			+ 1;
		computation->previous_indices[current_position] = previous_position;
	}
}

void	initialize_lis_tracking_for_position(t_lis_computation *computation,
		int current_position)
{
	computation->lis_lengths[current_position] = 1;
	computation->previous_indices[current_position] = -1;
}

/**
 * Computes the Longest Increasing Subsequence using dynamic programming.
 *
 * - For each element, check all previous elements to extend LIS
 * - Maintains lis_lengths[i] (length) and previous_indices[i] (predecessor) arrays
 */
void	compute_longest_increasing_lengths(t_lis_computation *computation,
		t_lis_result *best_result)
{
	int	current_position;
	int	previous_position;

	best_result->best_len = 0;
	best_result->best_end = 0;
	current_position = 0;
	while (current_position < computation->n)
	{
		initialize_lis_tracking_for_position(computation,
			current_position);
		previous_position = 0;
		while (previous_position < current_position)
		{
			try_extend_lis_from_previous_element(computation,
				current_position, previous_position);
			previous_position++;
		}
		update_best_lis_if_improved(computation, best_result,
			current_position);
		current_position++;
	}
}