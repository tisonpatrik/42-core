/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:25:49 by patrik            #+#    #+#             */
/*   Updated: 2025/09/12 19:21:00 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>
#include <stdlib.h>



/**
 * Executes the complete LIS computation algorithm.
 */
t_node_bool_array	*execute_lis_algorithm(t_stack *stack, int element_count)
{
	t_lis_computation	*computation;
	t_lis_result			result;
	t_node_bool_array	*final_result;

	computation = allocate_lis_arena(element_count);
	if (!computation)
		return (NULL);
	extract_stack_values_to_computation(stack, computation);
	compute_longest_increasing_lengths(computation, &result);
	final_result = build_lis_result(computation, &result);
	free_lis_arena(computation);
	return (final_result);
}

void get_empty_result(t_node_bool_array *result)
{
	result = malloc(sizeof(*result));
	if (!result)
		return ;
	result->items = NULL;
	result->count = 0;
}

/**
 * Finds the Longest Increasing Subsequence (LIS) in a stack.
 */
t_node_bool_array	*get_lis_nodes(t_stack *stack)
{
	int					stack_size;
	t_node_bool_array	*result;

	stack_size = get_size(stack);
	if (stack_size <= 0)
	{
		get_empty_result(result);
		return (result);
	}
	return (execute_lis_algorithm(stack, stack_size));
}

