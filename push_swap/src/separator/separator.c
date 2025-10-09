/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:32 by ptison            #+#    #+#             */
/*   Updated: 2025/10/09 11:35:37 by ptison           ###   ########.fr       */
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
		t_separator_arena *arena, int *breaks)
{
	int	size;

	get_lis_nodes(state->a, arena);
	size = get_size(state->a);
	if (size <= 1)
	{
		*breaks = 0;
	}
	else
	{
		*breaks = get_count_of_breaks(state->a, size);
	}
	return (true);
}

/*
 * Determines separation strategy based on LIS quality metrics.
 *
 * Uses reverse chain strategy when:
 * - LIS length is less than 30% of total elements (poor LIS quality)
 * - AND there are many breaks in the sequence (nearly sorted)
 *
 * @param n: Total number of elements
 * @param lis_len: Length of computed LIS
 * @param breaks: Number of breaks in the sequence
 * @return: true if reverse chain mode should be used,
	false for normal processing
 */
static bool	is_reverse_strategy(int n, size_t lis_len, int breaks)
{
	const double	lis_treshold_percent = 0.30;
	const int		min_breaks_treshold = n - 2;
	bool			poor_lis_quality;
	bool			many_breaks;

	poor_lis_quality = (double)lis_len < (double)n * lis_treshold_percent;
	many_breaks = breaks >= min_breaks_treshold;
	return (poor_lis_quality && many_breaks);
}

static void	execute_separation_strategy(t_sorting_state *state,
		t_separator_arena *arena, int breaks)
{
	if (is_reverse_strategy(get_size(state->a), arena->lis_length, breaks))
	{
		reverse_chain_mode(state);
	}
	else
	{
		process_stack_elements(state, get_size(state->a), arena->lis_nodes);
	}
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
	int					breaks;

	size_a = get_size(state->a);
	if (size_a <= 3)
		return ;
	arena = allocate_separator_arena(size_a);
	if (!arena)
		return ;
	if (!compute_lis_and_metrics(state, arena, &breaks))
	{
		free_separator_arena(arena);
		return ;
	}
	execute_separation_strategy(state, arena, breaks);
	free_separator_arena(arena);
}
