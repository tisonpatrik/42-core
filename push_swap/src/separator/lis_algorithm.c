/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:35:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/09 20:52:41 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>
#include <stdlib.h>

/* Forward declarations for memory management functions */
t_node_bool_array	*allocate_lis_memory(t_allocation_data *data);
int					extract_stack_values_to_arrays(t_stack *stack,
						t_node **nodes, int *values, int count);
void				free_lis_computation_memory(t_node **nodes, int *values,
						int *subsequence_lengths, int *previous_indices);

/* Forward declarations for result building */
t_node_bool_array	*build_lis_result(t_lis_arrays *arrays,
						t_lis_result *lis_result);

void	initialize_lis_tracking_for_position(t_lis_comp_data *computation_data,
		int current_position)
{
	computation_data->lis[current_position] = 1;
	computation_data->prev[current_position] = -1;
}

void	try_extend_lis_from_previous_element(t_lis_comp_data *data,
		int current_position, int previous_position)
{
	if (computation_data->vals[previous_position] < data->vals[current_position]
		&& computation_data->lis[previous_position]
		+ 1 > computation_data->lis[current_position])
	{
		data->lis[current_position] = computation_data->lis[previous_position]
			+ 1;
		data->prev[current_position] = previous_position;
	}
}

void	update_best_lis_if_improved(t_lis_comp_data *computation_data,
		t_lis_result *best_result, int current_position)
{
	if (computation_data->lis[current_position] >= best_result->best_len)
	{
		best_result->best_len = computation_data->lis[current_position];
		best_result->best_end = current_position;
	}
}

/**
 * Executes the complete LIS computation algorithm.
 */
t_node_bool_array	*execute_lis_algorithm(t_stack *stack, int element_count)
{
	t_lis_arrays			algorithm_data;
	t_lis_result			computation_result;
	t_lis_comp_data	computation_input;
	t_allocation_data		memory_allocation;
	t_node_bool_array		*final_result;

	memory_allocation.n = element_count;
	memory_allocation.nodes = &algorithm_data.nodes;
	memory_allocation.vals = &algorithm_data.vals;
	memory_allocation.lis = &algorithm_data.lis;
	memory_allocation.prev = &algorithm_data.prev;
	if (!allocate_lis_memory(&memory_allocation))
		return (NULL);
	extract_stack_values_to_arrays(stack, algorithm_data.nodes,
		algorithm_data.vals, element_count);
	computation_input.vals = algorithm_data.vals;
	computation_input.n = element_count;
	computation_input.lis = algorithm_data.lis;
	computation_input.prev = algorithm_data.prev;
	compute_longest_increasing_lengths(&computation_input, &computation_result);
	final_result = build_lis_result(&algorithm_data,
			&computation_result);
	free_lis_computation_memory(algorithm_data.nodes, algorithm_data.vals,
		algorithm_data.lis, algorithm_data.prev);
	return (final_result);
}

/**
 * Computes the Longest Increasing Subsequence using dynamic programming.
 *
 * - For each element, check all previous elements to extend LIS
 * - Maintains lis[i] (length) and prev[i] (predecessor) arrays
 */
void	compute_longest_increasing_lengths(t_lis_comp_data *computation_data,
		t_lis_result *best_result)
{
	int	current_position;
	int	previous_position;

	best_result->best_len = 0;
	best_result->best_end = 0;
	current_position = 0;
	while (current_position < computation_data->n)
	{
		initialize_lis_tracking_for_position(computation_data,
			current_position);
		previous_position = 0;
		while (previous_position < current_position)
		{
			try_extend_lis_from_previous_element(computation_data,
				current_position, previous_position);
			previous_position++;
		}
		update_best_lis_if_improved(computation_data, best_result,
			current_position);
		current_position++;
	}
}
