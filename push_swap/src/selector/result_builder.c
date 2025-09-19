/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:46:02 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 23:08:14 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>
#include <stdio.h>

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
