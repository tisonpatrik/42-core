/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 21:55:29 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

t_selector_config	default_selector_config(void)
{
	t_selector_config	config;

	config.max_candidates = 30;
	config.cost_threshold_offset = 1;
	config.size_penalty_factor = 10;
	config.heuristic_offset = 1;
	config.heuristic_divisor = 2;
	return (config);
}

bool	better_position(t_position a, t_position b)
{
	if (a.total != b.total)
		return (a.total < b.total);
	if (ft_abs(a.cost_a) != ft_abs(b.cost_a))
		return (ft_abs(a.cost_a) < ft_abs(b.cost_a));
	if (a.to_index != b.to_index)
		return (a.to_index < b.to_index);
	return (a.from_index < b.from_index);
}

t_candidate	new_candidate(t_position pos, int score)
{
	t_candidate	candidate;

	candidate.position = pos;
	candidate.score = score;
	return (candidate);
}

t_candidate	*filter_candidates_by_threshold(t_candidate *candidates, 
	int count, int threshold_offset, int *filtered_count)
{
	int			min_base_cost;
	int			threshold;
	t_candidate	*filtered;
	int			i;
	int			j;

	if (count == 0)
	{
		*filtered_count = 0;
		return (NULL);
	}
	min_base_cost = INT_MAX;
	i = 0;
	while (i < count)
	{
		if (candidates[i].position.total < min_base_cost)
			min_base_cost = candidates[i].position.total;
		i++;
	}
	threshold = min_base_cost + threshold_offset;
	filtered = malloc(sizeof(t_candidate) * count);
	if (!filtered)
		return (NULL);
	j = 0;
	i = 0;
	while (i < count)
	{
		if (candidates[i].position.total <= threshold)
		{
			filtered[j] = candidates[i];
			j++;
		}
		i++;
	}
	*filtered_count = j;
	return (filtered);
}

static int	compare_candidates(const void *a, const void *b)
{
	const t_candidate	*candidate_a = (const t_candidate *)a;
	const t_candidate	*candidate_b = (const t_candidate *)b;

	if (candidate_a->score != candidate_b->score)
		return (candidate_a->score - candidate_b->score);
	// Use BetterPosition for tie-breakers
	if (better_position(candidate_a->position, candidate_b->position))
		return (-1);
	return (1);
}

t_candidate	*select_top_k_candidates(t_candidate *candidates, 
	int count, int max_k, int *result_count)
{
	t_candidate	*sorted;
	int			result_size;

	if (count == 0)
	{
		*result_count = 0;
		return (NULL);
	}
	sorted = malloc(sizeof(t_candidate) * count);
	if (!sorted)
		return (NULL);
	ft_memcpy(sorted, candidates, sizeof(t_candidate) * count);
	qsort(sorted, count, sizeof(t_candidate), compare_candidates);
	if (max_k > 0 && max_k < count)
		result_size = max_k;
	else
		result_size = count;
	*result_count = result_size;
	return (sorted);
}

t_position	select_best_candidate(t_candidate *candidates, int count)
{
	t_position	best;
	int			i;

	if (count == 0)
	{
		best.total = INT_MAX;
		return (best);
	}
	best = candidates[0].position;
	i = 1;
	while (i < count)
	{
		if (better_position(candidates[i].position, best))
			best = candidates[i].position;
		i++;
	}
	return (best);
}

int	merged_cost(int a, int b)
{
	bool	same;

	same = (a >= 0 && b >= 0) || (a < 0 && b < 0);
	if (same)
	{
		if (ft_abs(a) > ft_abs(b))
			return (ft_abs(a));
		return (ft_abs(b));
	}
	return (ft_abs(a) + ft_abs(b));
}

int	signed_cost(int idx, int size)
{
	if (idx <= size / 2)
		return (idx);
	return (idx - size);
}

bool	is_empty(int *arr, int size)
{
	(void)arr;
	return (size == 0);
}

bool	is_empty_or_single(int *arr, int size)
{
	(void)arr;
	return (size <= 1);
}
