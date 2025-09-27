/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookahead_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:49:22 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:30 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>

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
 * Calculates a heuristic score for the current stack state.
 *
 * The heuristic combines breakpoint count with stack size to estimate
 * the remaining work needed to sort the stack. The formula:
 * - Raw score = breakpoints + stack_size
 * - Final score = (raw_score / size_penalty) / heuristic_divisor
 *
 * This provides a normalized estimate that considers both the
 * current disorder (breakpoints) and the scale of the problem (size).
 *
 * @param arena: Selector arena containing configuration and stack state
 * @return: Calculated heuristic score
 */
static int	calculate_heuristic(t_selector_arena *arena)
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

/*
 * Calculates the total score for a candidate position.
 *
 * The score combines:
 * 1. Rotation cost: merged_cost(cost_a, cost_b) + 1 (for the push operation)
 * 2. Heuristic estimate: estimated remaining work after this move
 *
 * This provides a comprehensive evaluation that considers both
 * the immediate cost of the move and its impact on future sorting.
 *
 * @param position: Candidate position with rotation costs
 * @param arena: Selector arena containing configuration and state
 * @return: Total score for the candidate
 */
static int	calculate_score(t_position position, t_selector_arena *arena)
{
	int	rotation_cost;
	int	heuristic_estimate;

	rotation_cost = merged_cost(position.cost_a, position.cost_b) + 1;
	heuristic_estimate = calculate_heuristic(arena);
	return (heuristic_estimate + rotation_cost);
}

/*
 * Finds the best candidate among the provided candidates.
 *
 * This function evaluates all candidates using the calculate_score()
 * function and selects the one with the lowest score. When scores
 * are equal, it uses is_better_position() as a tie-breaker to ensure
 * deterministic selection.
 *
 * @param candidates: Array of candidates to evaluate
 * @param count: Number of candidates in the array
 * @param arena: Selector arena containing configuration and state
 * @return: Position of the best candidate
 */
static t_position	find_best_candidate(t_candidate *candidates, int count,
		t_selector_arena *arena)
{
	t_position	best_position;
	int			i;
	int			best_score;
	int			current_score;

	best_position = candidates[0].position;
	best_score = calculate_score(best_position, arena);
	i = 1;
	while (i < count)
	{
		current_score = calculate_score(candidates[i].position, arena);
		if (current_score < best_score || (current_score == best_score
				&& is_better_position(candidates[i].position, best_position)))
		{
			best_position = candidates[i].position;
			best_score = current_score;
		}
		i++;
	}
	return (best_position);
}

t_position	evaluate_with_lookahead(t_candidate *candidates,
		t_selector_arena *arena)
{
	t_position	invalid_position;

	if (!arena || !arena->snapshot_arena || !candidates
		|| arena->top_k_count == 0)
	{
		invalid_position.total = INT_MAX;
		return (invalid_position);
	}
	return (find_best_candidate(candidates, arena->top_k_count, arena));
}
