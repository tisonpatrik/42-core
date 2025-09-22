/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candidates_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:15:11 by patrik            #+#    #+#             */
/*   Updated: 2025/09/22 11:14:09 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>

/*
 * Sorts candidates by cost using bubble sort algorithm.
 *
 * This function implements a simple bubble sort to order candidates
 * by their cost using the compare_candidates() function. The sorting
 * ensures that candidates with lower costs appear first in the array.

 * @param candidates: Array of candidates to sort
 * @param count: Number of candidates in the array
 */
static void	sort_candidates_by_cost(t_candidate *candidates, int count)
{
	t_candidate	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (compare_candidates(&candidates[j], &candidates[j + 1]) > 0)
			{
				tmp = candidates[j];
				candidates[j] = candidates[j + 1];
				candidates[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/*
 * Builds the top-k candidates from filtered candidates.
 *
 * This function implements the final selection phase:
 * 1. Sorts filtered candidates by cost using bubble sort
 * 2. Selects the top k candidates (or all if k > count)
 * 3. Copies the selected candidates to the arena's top_k_candidates array
 * 4. Updates the top_k_count in the arena
 *
 * The top-k selection ensures that only the most promising candidates
 * are passed to the lookahead evaluator, balancing performance with
 * solution quality.
 *
 * @param candidates: Array of filtered candidates to select from
 * @param max_k: Maximum number of candidates to select
 * @param arena: Selector arena containing storage arrays and metadata
 * @return: Array of top-k candidates, or NULL if no candidates available
 */
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
	if (max_k > 0 && max_k < n)
		k = max_k;
	else
		k = n;
	ft_memcpy(arena->top_k_candidates, candidates, sizeof(t_candidate) * k);
	arena->top_k_count = k;
	return (arena->top_k_candidates);
}
