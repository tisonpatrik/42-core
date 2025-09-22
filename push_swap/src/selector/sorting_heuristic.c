/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_heuristic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:32:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/17 22:32:00 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

/*
 * Counts breakpoints in stack A to assess sorting progress.
 *
 * A breakpoint occurs when an element is greater than the next element
 * in the circular stack. This function counts both internal breakpoints
 * (between consecutive elements) and the circular breakpoint (between
 * last and first elements).
 *
 * Fewer breakpoints indicate better sorting progress, making this
 * a useful heuristic for evaluating candidate moves.
 *
 * @param arena: Selector arena containing stack A snapshot
 * @return: Number of breakpoints found in stack A
 */
static int	count_breakpoints(t_selector_arena *arena)
{
	int	breakpoints;
	int	i;
	int	*a_values;
	int	size_a;

	breakpoints = 0;
	i = 0;
	a_values = arena->snapshot_arena->a_values;
	size_a = arena->snapshot_arena->size_a;
	while (i < size_a - 1)
	{
		if (a_values[i] > a_values[i + 1])
			breakpoints++;
		i++;
	}
	if (a_values[size_a - 1] > a_values[0])
		breakpoints++;
	return (breakpoints);
}

/*
 * Calculates a sorting heuristic score for the current stack state.
 *
 * The heuristic combines breakpoint count with stack size to estimate
 * the remaining work needed to sort the stack. The formula:
 * - Raw score = breakpoints + stack_size
 * - Final score = (raw_score / size_penalty) / heuristic_divisor
 *
 * This provides a normalized estimate that considers both the
 * current disorder (breakpoints) and the scale of the problem (size).
 * Lower scores indicate better sorting progress.
 *
 * @param arena: Selector arena containing configuration and stack state
 * @return: Calculated sorting heuristic score
 */
int	calculate_sorting_heuristic(t_selector_arena *arena)
{
	int	breakpoints;
	int	raw_score;
	int	size_penalty;

	if (arena->snapshot_arena->size_a <= 1)
		return (0);
	breakpoints = count_breakpoints(arena);
	raw_score = breakpoints + arena->snapshot_arena->size_a;
	size_penalty = arena->config.size_penalty_factor
		+ arena->config.heuristic_offset;
	return ((raw_score / size_penalty) / arena->config.heuristic_divisor);
}
