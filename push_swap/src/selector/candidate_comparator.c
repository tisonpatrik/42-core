/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candidate_comparator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:23:46 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 11:25:23 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

/*
 * Compares candidates based on primary criteria: score and total cost.
 *
 * Primary comparison criteria (in order of priority):
 * 1. Score: Lower score indicates better candidate
 * 2. Total cost: Lower total rotation cost is preferred
 *
 * This ensures that candidates with better overall evaluation
 * are ranked higher in the selection process.
 *
 * @param a: First candidate to compare
 * @param b: Second candidate to compare
 * @return: Negative if a < b, positive if a > b, 0 if equal
 */
static int	compare_primary_criteria(const t_candidate *a, const t_candidate *b)
{
	if (a->score != b->score)
	{
		if (a->score < b->score)
			return (-1);
		else
			return (1);
	}
	if (a->position.total != b->position.total)
	{
		if (a->position.total < b->position.total)
			return (-1);
		else
			return (1);
	}
	return (0);
}

/*
 * Compares candidates based absolute cost of stack A rotations.
 * Secondary comparison criteria:
 * - Absolute cost of stack A rotations: Lower absolute cost is preferred
 *
 * This tie-breaker ensures that when candidates have equal primary scores,
 * the one requiring fewer rotations of stack A is chosen, which is generally
 * more efficient for the overall sorting process.
 *
 * @param a: First candidate to compare
 * @param b: Second candidate to compare
 * @return: Negative if a < b, positive if a > b, 0 if equal
 */
static int	compare_cost_criteria(const t_candidate *a, const t_candidate *b)
{
	int	absa;
	int	absb;

	absa = ft_abs(a->position.cost_a);
	absb = ft_abs(b->position.cost_a);
	if (absa != absb)
	{
		if (absa < absb)
			return (-1);
		else
			return (1);
	}
	return (0);
}

/*
 * Compares candidates based on index criteria: target and source positions.
 *
 * Tertiary comparison criteria (in order of priority):
 * 1. Target index in stack A: Lower index preferred (closer to top)
 * 2. Source index in stack B: Lower index preferred (closer to top)
 *
 * This final tie-breaker ensures deterministic ordering when all other
 * criteria are equal, preferring moves that involve elements closer
 * to the top of their respective stacks.
 *
 * @param a: First candidate to compare
 * @param b: Second candidate to compare
 * @return: Negative if a < b, positive if a > b, 0 if equal
 */
static int	compare_index_criteria(const t_candidate *a, const t_candidate *b)
{
	if (a->position.to_index != b->position.to_index)
	{
		if (a->position.to_index < b->position.to_index)
			return (-1);
		else
			return (1);
	}
	if (a->position.from_index != b->position.from_index)
	{
		if (a->position.from_index < b->position.from_index)
			return (-1);
		else
			return (1);
	}
	return (0);
}

int	compare_candidates(const void *a, const void *b)
{
	const t_candidate	*atemp = (const t_candidate *)a;
	const t_candidate	*btemp = (const t_candidate *)b;
	int					result;

	result = compare_primary_criteria(atemp, btemp);
	if (result != 0)
		return (result);
	result = compare_cost_criteria(atemp, btemp);
	if (result != 0)
		return (result);
	result = compare_index_criteria(atemp, btemp);
	return (result);
}
