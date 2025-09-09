/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_result_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:35:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/09 20:29:14 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include <stdbool.h>
#include <stdlib.h>


void	reconstruct_lis_sequence_from_tracking(
		t_node_bool_array *result, t_lis_arrays *algorithm_data,
		t_lis_result *computation_result)
{
	size_t	result_index;
	int		current_index;

	result_index = 0;
	current_index = computation_result->best_end;
	while (current_index != -1 && result_index
		< (size_t)computation_result->best_len)
	{
		result->items[result_index].node = algorithm_data->nodes[current_index];
		result->items[result_index].value = true;
		result_index++;
		current_index = algorithm_data->prev[current_index];
	}
	result->count = result_index;
}


void	reverse_sequence_to_correct_order(t_node_bool_array *result)
{
	size_t		swap_index;
	t_node_bool	temporary_node;

	swap_index = 0;
	while (swap_index < result->count / 2)
	{
		temporary_node = result->items[swap_index];
		result->items[swap_index] = result->items[result->count - 1
			- swap_index];
		result->items[result->count - 1 - swap_index] = temporary_node;
		swap_index++;
	}
}

/**
 * Builds the LIS result array from computation data.
 */
t_node_bool_array	*build_lis_result_from_computation(
			t_lis_arrays *algorithm_data,
			t_lis_result *computation_result)
{
	t_node_bool_array	*result;

	result = malloc(sizeof(*result));
	if (!result)
		return (NULL);
	result->items = ft_calloc((size_t)computation_result->best_len,
		sizeof(t_node_bool));
	if (!result->items)
	{
		free(result);
		return (NULL);
	}
	reconstruct_lis_sequence_from_tracking(result, algorithm_data, computation_result);
	reverse_sequence_to_correct_order(result);
	return (result);
}
