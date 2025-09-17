/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candidates_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:15:11 by patrik            #+#    #+#             */
/*   Updated: 2025/09/17 20:10:53 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

#include <stdbool.h>


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

void	sort_candidates_by_cost(t_candidate *candidates, int count)
{
	t_candidate	tmp;
	int i;
	int j;

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
