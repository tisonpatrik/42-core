/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:46:02 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 20:48:41 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>
#include <stdio.h>

int	calculate_threshold(t_candidate *candidates, int count,
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

int	compare_candidates(const void *a, const void *b)
{
	const t_candidate	*atemp = (const t_candidate *)a;
	const t_candidate	*btemp = (const t_candidate *)b;
	int					absa;
	int					absb;

	if (atemp->score != btemp->score)
		return ((atemp->score < btemp->score) ? -1 : 1);
	if (atemp->position.total != btemp->position.total)
		return ((atemp->position.total < btemp->position.total) ? -1 : 1);
	absa = ft_abs(atemp->position.cost_a);
	absb = ft_abs(btemp->position.cost_a);
	if (absa != absb)
		return ((absa < absb) ? -1 : 1);
	if (atemp->position.to_index != btemp->position.to_index)
		return ((atemp->position.to_index < btemp->position.to_index) ? -1 : 1);
	if (atemp->position.from_index != btemp->position.from_index)
		return ((atemp->position.from_index < btemp->position.from_index) ? -1 : 1);
	return (0);
}

void	sort_candidates_by_cost(t_candidate *candidates, int count)
{
	t_candidate	tmp;

	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (compare_candidates(&candidates[j], &candidates[j + 1]) > 0)
			{
				tmp = candidates[j];
				candidates[j] = candidates[j + 1];
				candidates[j + 1] = tmp;
			}
		}
	}
}

t_candidate	*build_top_k_candidates(t_candidate *candidates, int max_k,
		t_selector_arena *arena)
{
	int	n;
	int	k;

	n = arena->filtered_count;
	if (n <= 0)
	{
		arena->top_k_count = 0;
		return (NULL);
	}
	sort_candidates_by_cost(candidates, n);
	k = (max_k > 0 && max_k < n) ? max_k : n;
	ft_memcpy(arena->top_k_candidates, candidates, sizeof(t_candidate) * k);
	arena->top_k_count = k;
	return (arena->top_k_candidates);
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
