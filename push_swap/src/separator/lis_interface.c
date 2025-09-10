/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_interface.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:25:49 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 21:11:27 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>
#include <stdlib.h>

/* Forward declaration for algorithm execution */
t_node_bool_array	*execute_lis_algorithm(t_stack *stack, int element_count);

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
		result = malloc(sizeof(*result));
		if (!result)
			return (NULL);
		result->items = NULL;
		result->count = 0;
		return (result);
	}
	return (execute_lis_algorithm(stack, stack_size));
}
