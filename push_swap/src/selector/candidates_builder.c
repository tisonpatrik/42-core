/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candidates_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:15:11 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 22:20:27 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

#include <stdbool.h>


int	compare_candidates(const void *a, const void *b)
{
	const t_candidate	*atemp = (const t_candidate *)a;
	const t_candidate	*btemp = (const t_candidate *)b;
	int					absa;
	int					absb;

	if (atemp->score != btemp->score)
	{
		if (atemp->score < btemp->score)
			return (-1);
		else
			return (1);
	}
	if (atemp->position.total != btemp->position.total)
	{
		if (atemp->position.total < btemp->position.total)
			return (-1);
		else
			return (1);
	}
	absa = ft_abs(atemp->position.cost_a);
	absb = ft_abs(btemp->position.cost_a);
	if (absa != absb)
	{
		if (absa < absb)
			return (-1);
		else
			return (1);
	}
	if (atemp->position.to_index != btemp->position.to_index)
	{
		if (atemp->position.to_index < btemp->position.to_index)
			return (-1);
		else
			return (1);
	}
	if (atemp->position.from_index != btemp->position.from_index)
	{
		if (atemp->position.from_index < btemp->position.from_index)
			return (-1);
		else
			return (1);
	}
	return (0);
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
