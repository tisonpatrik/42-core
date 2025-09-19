/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candidate_enumerator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:41:17 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 23:07:30 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include "../../include/snapshot_arena.h"
#include <stdbool.h>
#include <stdio.h>

static t_candidate	get_candidate(int from_idx, int to_idx, int size_a, int size_b)
{
	t_position	pos;
	int			cost_a;
	int			cost_b;
	t_candidate	candidate;

	cost_a = signed_cost(to_idx, size_a);
	cost_b = signed_cost(from_idx, size_b);
	pos.total = merged_cost(cost_a, cost_b);
	pos.cost_a = cost_a;
	pos.cost_b = cost_b;
	pos.from_index = from_idx;
	pos.to_index = to_idx;
	candidate.position = pos;
	candidate.score = pos.total;
	return (candidate);
}

static void	populate_candidates(t_snapshot_arena *snapshot,
		t_selector_arena *arena)
{
	t_candidate	*result;
	int			candidate_idx;
	int			i;
	int			target_pos;

	result = arena->candidates;
	candidate_idx = 0;
	i = 0;
	while (i < snapshot->size_b)
	{
		target_pos = find_target_position(snapshot->a_values, snapshot->size_a,
				snapshot->b_values[i]);
		result[candidate_idx] = get_candidate(i, target_pos, snapshot->size_a,
				snapshot->size_b);
		candidate_idx++;
		i++;
	}
	arena->candidate_count = candidate_idx;
}

t_candidate	*enumerate_candidates(t_sorting_state *state,
		t_selector_arena *arena)
{
	if (!take_snapshots(arena->snapshot_arena, state->a, state->b))
		return (NULL);
	if (arena->snapshot_arena->size_b == 0)
	{
		arena->candidate_count = 0;
		return (NULL);
	}
	populate_candidates(arena->snapshot_arena, arena);
	return (arena->candidates);
}
