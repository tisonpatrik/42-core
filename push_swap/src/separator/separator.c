/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 19:30:26 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"

/*
 * Entry point for the separator module.
 *
 * This function orchestrates the entire separation process:
 * 1. Validates input and handles edge cases (size <= 3)
 * 2. Allocates memory arena for LIS computation
 * 3. Computes the longest increasing subsequence
 * 4. Processes stack elements to separate LIS from non-LIS elements
 * 5. Cleans up allocated memory
 *
 * @param state: The sorting state containing both stacks
 */
void	push_non_lis_into_b(t_sorting_state *state)
{
	t_separator_arena	*arena;
	t_node				**lis_nodes;
	int					size_a;

	size_a = get_size(state->a);
	if (size_a <= 3)
		return ;
	arena = allocate_separator_arena(size_a);
	if (!arena)
		return ;
	lis_nodes = get_lis_nodes(state->a, arena);
	if (!lis_nodes)
	{
		free_separator_arena(arena);
		return ;
	}
	process_stack_elements(state, size_a, lis_nodes);
	free_separator_arena(arena);
}
