/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:25:30 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 20:52:06 by ptison           ###   ########.fr       */
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


void	get_lis_nodes(t_stack *stack, t_separator_arena *arena)
{
	t_lis_result	result;
	extract_stack_values_to_computation(stack, arena->computation);
	compute_longest_increasing_lens(arena->computation, &result);
	build_lis_result(arena->computation, &result, arena);
}
