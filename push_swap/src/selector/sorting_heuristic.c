/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_heuristic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:32:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/17 22:32:00 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

static int	count_breakpoints(t_selector_arena *arena)
{
	int	breakpoints;
	int	i;
	int	*a_values;
	int	size_a;

	breakpoints = 0;
	i = 0;
	a_values = arena->snapshot_arena->a_values;
	size_a = arena->snapshot_arena->size_a;
	while (i < size_a - 1)
	{
		if (a_values[i] > a_values[i + 1])
			breakpoints++;
		i++;
	}
	if (a_values[size_a - 1] > a_values[0])
		breakpoints++;
	return (breakpoints);
}

int	calculate_sorting_heuristic(t_selector_arena *arena)
{
	int	breakpoints;
	int	raw_score;
	int	size_penalty;

	if (arena->snapshot_arena->size_a <= 1)
		return (0);
	breakpoints = count_breakpoints(arena);
	raw_score = breakpoints + arena->snapshot_arena->size_a;
	size_penalty = arena->config.size_penalty_factor
		+ arena->config.heuristic_offset;
	return ((raw_score / size_penalty) / arena->config.heuristic_divisor);
}
