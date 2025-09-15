/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/15 21:55:42 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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
		if (candidates[i].position.total <= threshold && arena->filtered_count < arena->max_candidates)
		{
			filtered[arena->filtered_count] = candidates[i];
			arena->filtered_count++;
		}
		i++;
	}
	return (filtered);
}

int compare_candidates(const void *a, const void *b)
{
    const t_candidate *A = (const t_candidate *)a;
    const t_candidate *B = (const t_candidate *)b;

    if (A->score != B->score)
        return (A->score < B->score) ? -1 : 1;

    if (A->position.total != B->position.total)
        return (A->position.total < B->position.total) ? -1 : 1;

    int absA = ft_abs(A->position.cost_a);
    int absB = ft_abs(B->position.cost_a);
    if (absA != absB)
        return (absA < absB) ? -1 : 1;

    if (A->position.to_index != B->position.to_index)
        return (A->position.to_index < B->position.to_index) ? -1 : 1;

    if (A->position.from_index != B->position.from_index)
        return (A->position.from_index < B->position.from_index) ? -1 : 1;

    return 0;
}

void sort_candidates_by_cost(t_candidate *candidates, int count)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (compare_candidates(&candidates[j], &candidates[j + 1]) > 0) {
                t_candidate tmp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = tmp;
            }
        }
    }
}

t_candidate *build_top_k_candidates(t_candidate *candidates, int max_k, t_selector_arena *arena)
{
    int n = arena->filtered_count;
    if (n <= 0) {
        arena->top_k_count = 0;
        return NULL; // nebo vra\u0165 pointer + count=0, podle sjednocen� politiky
    }

    // 1) se\u0159adit cel� pole
    sort_candidates_by_cost(candidates, n);

    // 2) vybrat prvn�ch K (nebo v\u0161echno)
    int k = (max_k > 0 && max_k < n) ? max_k : n;

    ft_memcpy(arena->top_k_candidates, candidates, sizeof(t_candidate) * k);
    arena->top_k_count = k;
	
	return arena->top_k_candidates;
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
