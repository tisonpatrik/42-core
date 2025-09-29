/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_computation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:25:30 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 19:34:14 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"

static int	extract_stack_values_to_computation(t_stack *stack,
		t_lis_computation *computation)
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
