/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:46:02 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>
#include <stdio.h>

/*
 * Calculates the cost threshold for candidate filtering.
 *
 * The threshold is determined by finding the minimum base cost among all
 * candidates and adding a configurable offset. This creates a dynamic
 * threshold that adapts to the current state of the stacks, ensuring
 * that only candidates within a reasonable cost range are considered.
 *
 * @param candidates: Array of all candidates to evaluate
 * @param count: Number of candidates in the array
 * @param threshold_offset: Configurable offset added to minimum cost
 * @return: Calculated threshold value for filtering
 */
static int	calculate_threshold(t_candidate *candidates, int count,
		int threshold_offset)
{
	int	min_base_cost;
	int	i;
	int	threshold;

	min_base_cost = INT_MAX;
	i = 0;
	while (i < count)
	{
		if (candidates[i].position.total < min_base_cost)
			min_base_cost = candidates[i].position.total;
		i++;
	}
	threshold = min_base_cost + threshold_offset;
	return (threshold);
}

/*
 * Filters candidates based on cost threshold and maximum count limits.
 *
 * This function implements the filtering phase of the selector algorithm:
 * 1. Calculates a dynamic threshold based on the minimum cost + offset
 * 2. Filters candidates that fall within the threshold
 * 3. Respects the maximum candidate count limit
 * 4. Stores filtered results in the arena's filtered_candidates array
 *
 * The filtering process reduces the search space by eliminating
 * candidates that are too expensive, improving performance while
 * maintaining solution quality.
 *
 * @param candidates: Array of all candidates to filter
 * @param threshold_offset: Offset added to minimum cost for threshold calc
 * @param arena: Selector arena containing configuration and storage arrays
 * @return: Array of filtered candidates, or NULL if no candidates pass filter
 */
t_candidate	*build_filtered_candidates(t_candidate *candidates,
		int threshold_offset, t_selector_arena *arena)
{
	int			threshold;
	t_candidate	*filtered;
	int			i;
	int			count;

	count = arena->candidate_count;
	if (count == 0)
		return (NULL);
	threshold = calculate_threshold(candidates, count, threshold_offset);
	filtered = arena->filtered_candidates;
	arena->filtered_count = 0;
	i = 0;
	while (i < count)
	{
		if (candidates[i].position.total <= threshold
			&& arena->filtered_count < arena->max_candidates)
		{
			filtered[arena->filtered_count] = candidates[i];
			arena->filtered_count++;
		}
		i++;
	}
	return (filtered);
}
