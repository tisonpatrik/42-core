/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookahead_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:49:22 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 22:26:15 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>

int	calculate_heuristic_without_copy(t_selector_arena *arena)
{
	int	breakpoints;
	int	i;

	if (arena->snapshot_arena->size_a <= 1)
		return (0);
	breakpoints = 0;
	i = 0;
	while (i < arena->snapshot_arena->size_a - 1)
	{
		if (arena->snapshot_arena->a_values[i] > arena->snapshot_arena->a_values[i
			+ 1])
			breakpoints++;
		i++;
	}
	if (arena->snapshot_arena->a_values[arena->snapshot_arena->size_a
		- 1] > arena->snapshot_arena->a_values[0])
		breakpoints++;
	return ((breakpoints + arena->snapshot_arena->size_a
			/ arena->config.size_penalty_factor
			+ arena->config.heuristic_offset)
		/ arena->config.heuristic_divisor);
}

int	calculate_score(t_position position, t_selector_arena *arena)
{
	int	rotation_cost;
	int	heuristic_estimate;

	rotation_cost = merged_cost(position.cost_a, position.cost_b) + 1;
	heuristic_estimate = calculate_heuristic_without_copy(arena);
	return (heuristic_estimate + rotation_cost);
}

t_position	find_best_candidate(t_candidate *candidates,
		t_selector_arena *arena)
{
	t_position	best_position;
	int			i;
	int			best_score;
	int			current_score;

	best_position = candidates[0].position;
	best_score = calculate_score(best_position, arena);
	i = 1;
	while (i < arena->top_k_count)
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
	return (find_best_candidate(candidates, arena));
}
