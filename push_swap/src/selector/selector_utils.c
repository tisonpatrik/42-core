/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:14:42 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 23:16:16 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

bool	better_position(t_position a, t_position b)
{
	if (a.total != b.total)
		return (ft_less_than(a.total, b.total));
	if (ft_abs(a.cost_a) != ft_abs(b.cost_a))
		return (ft_less_than(ft_abs(a.cost_a), ft_abs(b.cost_a)));
	if (a.to_index != b.to_index)
		return (ft_less_than(a.to_index, b.to_index));
	return (ft_less_than(a.from_index, b.from_index));
}

static int	find_minimum_cost(t_candidate *candidates, int count);

int	find_min_base_cost(t_candidate *candidates, int count)
{
	return (find_minimum_cost(candidates, count));
}

static int	find_minimum_cost(t_candidate *candidates, int count)
{
	int	min_cost;
	int	i;

	if (count == 0)
		return (INT_MAX);
	min_cost = candidates[0].position.total;
	i = 1;
	while (i < count)
	{
		if (candidates[i].position.total < min_cost)
			min_cost = candidates[i].position.total;
		i++;
	}
	return (min_cost);
}

int	calculate_threshold(t_candidate *candidates, int count,
	int threshold_offset)
{
	int	min_base_cost;

	min_base_cost = find_min_base_cost(candidates, count);
	return (min_base_cost + threshold_offset);
}

t_candidate	*filter_candidates_by_threshold(t_candidate *candidates,
	int count, int threshold_offset, int *filtered_count)
{
	int			threshold;
	t_candidate	*filtered;
	int			i;

	if (count == 0)
	{
		*filtered_count = 0;
		return (NULL);
	}
	threshold = calculate_threshold(candidates, count, threshold_offset);
	filtered = malloc(sizeof(t_candidate) * count);
	if (!filtered)
		return (NULL);
	*filtered_count = 0;
	i = 0;
	while (i < count)
	{
		if (candidates[i].position.total <= threshold)
		{
			filtered[*filtered_count] = candidates[i];
			(*filtered_count)++;
		}
		i++;
	}
	return (filtered);
}
