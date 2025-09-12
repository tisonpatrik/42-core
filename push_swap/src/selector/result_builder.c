/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/12 23:46:34 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>
#include <stdlib.h>

int	calculate_threshold(t_candidate *candidates, int count, int threshold_offset)
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
		if (candidates[i].position.total <= threshold)
		{
			filtered[arena->filtered_count] = candidates[i];
			arena->filtered_count++;
		}
		i++;
	}
	return (filtered);
}

static int	compare_candidates(const void *a, const void *b)
{
	t_candidate	*candidate_a;
	t_candidate	*candidate_b;

	candidate_a = (t_candidate *)a;
	candidate_b = (t_candidate *)b;
	if (candidate_a->position.total != candidate_b->position.total)
		return (candidate_a->position.total - candidate_b->position.total);
	if (ft_abs(candidate_a->position.cost_a) != ft_abs(candidate_b->position.cost_a))
		return (ft_abs(candidate_a->position.cost_a) - ft_abs(candidate_b->position.cost_a));
	if (candidate_a->position.to_index != candidate_b->position.to_index)
		return (candidate_a->position.to_index - candidate_b->position.to_index);
	return (candidate_a->position.from_index - candidate_b->position.from_index);
}


#include <stdio.h>
t_candidate	*build_top_k_candidates(t_candidate *candidates,
	int max_k, t_selector_arena *arena)
{
	t_candidate	*sorted_candidates;
	int			actual_k;
	int			filtered_count;
	int			i;
	int			j;


	filtered_count = arena->filtered_count;
	if (filtered_count == 0)
		return (NULL);
	if (filtered_count < max_k)
		actual_k = filtered_count;
	else
		actual_k = max_k;
	sorted_candidates = arena->top_k_candidates;
	ft_memcpy(sorted_candidates, candidates, sizeof(t_candidate) * filtered_count);
	// Simple bubble sort for small arrays
	i = 0;
	j = 0;
	while (i < filtered_count - 1)
	{
		while (j < filtered_count - i - 1)
		{
			if (compare_candidates(&sorted_candidates[j], &sorted_candidates[j + 1]) > 0)
			{
				t_candidate temp = sorted_candidates[j];
				sorted_candidates[j] = sorted_candidates[j + 1];
				sorted_candidates[j + 1] = temp;
			}
		}
	}
	arena->top_k_count = actual_k;
	
	// Print all candidates
	i = 0;
	while (i < actual_k)
	{
		printf("Candidate %d: total=%d, cost_a=%d, cost_b=%d, from_index=%d, to_index=%d, score=%d\n",
			i, sorted_candidates[i].position.total, sorted_candidates[i].position.cost_a,
			sorted_candidates[i].position.cost_b, sorted_candidates[i].position.from_index,
			sorted_candidates[i].position.to_index, sorted_candidates[i].score);
		i++;
	}
	
	return (sorted_candidates);
}

t_position	build_best_position(t_candidate *candidates)
{
	t_position	result;
	int			i;
	int			count;

	if (!candidates)
	{
		result.total = INT_MAX;
		return (result);
	}
	// For this function, we'll use a simple approach - assume candidates are valid
	// In practice, this would be called with arena->top_k_candidates
	count = 0;
	while (candidates[count].position.total != INT_MAX && count < 1000)
		count++;
	if (count == 0)
	{
		result.total = INT_MAX;
		return (result);
	}
	result = candidates[0].position;
	i = 1;
	while (i < count)
	{
		if (better_position(candidates[i].position, result))
			result = candidates[i].position;
		i++;
	}
	return (result);
}
