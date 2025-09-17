/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candidate_comparator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:23:46 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 22:23:49 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

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
