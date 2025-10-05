/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:32 by ptison            #+#    #+#             */
/*   Updated: 2025/10/05 20:22:13 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"

/*
 * Computes LIS and calculates separation metrics.
 *
 * @param state: The sorting state containing stack A
 * @param arena: Pre-allocated arena for LIS computation
 * @param lis_len: Output parameter for LIS length
 * @param breaks: Output parameter for break count
 * @return: true if computation successful, false otherwise
 */
static bool	compute_lis_and_metrics(t_sorting_state *state,
		t_separator_arena *arena, size_t *lis_len, int *breaks)
{
	get_lis_nodes(state->a, arena);
	*lis_len = 0;
	while (arena->lis_nodes[*lis_len])
		(*lis_len)++;
	*breaks = count_breaks(state->a);
	return (true);
}

/*
 * Determines separation strategy based on LIS quality metrics.
 *
 * @param state: The sorting state containing both stacks
 * @param arena: Arena to free if using reverse chain mode
 * @param lis_len: Length of computed LIS
 * @param breaks: Number of breaks in the sequence
 * @return: true if reverse chain mode was used, false if normal processing
 */
static bool	choose_separation_strategy(t_sorting_state *state,
		t_separator_arena *arena, size_t lis_len, int breaks)
{
	int	n;

	n = get_size(state->a);
	if ((lis_len * 10 < (size_t)n * 3) && (breaks >= n - 2))
	{
		reverse_chain_mode(state);
		free_separator_arena(arena);
		return (true);
	}
	return (false);
}

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
	int					size_a;
	size_t				lis_len;
	int					breaks;

	size_a = get_size(state->a);
	if (size_a <= 3)
		return ;
	arena = allocate_separator_arena(size_a);
	if (!arena)
		return ;
	if (!compute_lis_and_metrics(state, arena, &lis_len, &breaks))
	{
		free_separator_arena(arena);
		return ;
	}
	if (choose_separation_strategy(state, arena, lis_len, breaks))
		return ;
	process_stack_elements(state, size_a, arena->lis_nodes);
	free_separator_arena(arena);
}
