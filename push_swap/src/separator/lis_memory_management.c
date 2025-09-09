/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_memory_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:46 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 20:29:21 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>
#include <stdlib.h>

/* Forward declarations for functions defined in other files */
void					compute_longest_increasing_lengths(
							t_lis_computation_data *data, t_lis_result *result);
t_node_bool_array		*build_lis_result_from_computation(t_lis_arrays *arrays,
							t_lis_result *lis_result);


int	extract_stack_values_to_arrays(t_stack *stack,
				t_node **nodes, int *values, int count)
{
	t_node	*current_node;
	int		index;

	current_node = get_head(stack);
	index = 0;
	while (index < count)
	{
		nodes[index] = current_node;
		values[index] = get_content(current_node);
		current_node = get_next(current_node);
		index++;
	}
	return (0);
}


t_node_bool_array	*allocate_lis_computation_memory(
							t_allocation_data *allocation_data)
{
	*allocation_data->nodes = malloc(sizeof(**allocation_data->nodes)
			* (size_t)allocation_data->n);
	*allocation_data->vals = malloc(sizeof(**allocation_data->vals)
			* (size_t)allocation_data->n);
	if (!*allocation_data->nodes || !*allocation_data->vals)
	{
		free(*allocation_data->nodes);
		free(*allocation_data->vals);
		return (NULL);
	}
	*allocation_data->lis = malloc(sizeof(**allocation_data->lis)
			* (size_t)allocation_data->n);
	*allocation_data->prev = malloc(sizeof(**allocation_data->prev)
			* (size_t)allocation_data->n);
	if (!*allocation_data->lis || !*allocation_data->prev)
	{
		free(*allocation_data->lis);
		free(*allocation_data->prev);
		free(*allocation_data->nodes);
		free(*allocation_data->vals);
		return (NULL);
	}
	return ((t_node_bool_array *)1);
}


void	free_lis_computation_memory(t_node **nodes, int *values,
				int *subsequence_lengths, int *previous_indices)
{
	free(nodes);
	free(values);
	free(subsequence_lengths);
	free(previous_indices);
}








