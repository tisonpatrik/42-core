/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candidate_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:14:22 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:14:24 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

t_candidate	new_candidate(t_position pos, int score)
{
	t_candidate	candidate;

	candidate.position = pos;
	candidate.score = score;
	return (candidate);
}

static int	compare_candidates(const void *a, const void *b)
{
	const t_candidate	*candidate_a = (const t_candidate *)a;
	const t_candidate	*candidate_b = (const t_candidate *)b;

	if (candidate_a->score != candidate_b->score)
		return (candidate_a->score - candidate_b->score);
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
