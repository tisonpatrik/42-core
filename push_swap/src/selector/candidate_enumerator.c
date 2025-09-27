/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candidate_enumerator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:41:17 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:30 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include "../../include/snapshot_arena.h"
#include <stdbool.h>
#include <stdio.h>

/*
 * Creates a candidate move from stack B to stack A with calculated costs.
 *
 * This function calculates the optimal rotation costs for both stacks to
 * position an element from stack B at the correct position in stack A.
 * The costs are calculated using signed_cost() which determines whether
 * to rotate forward or backward based on the shortest path.
 *
 * @param from_idx: Index of element in stack B (0-based)
 * @param to_idx: Target index in stack A where element should be placed
 * @param size_a: Current size of stack A
 * @param size_b: Current size of stack B
 * @return: Candidate structure with position and cost information
 */
static t_candidate	get_candidate(int from_idx, int to_idx, int size_a,
		int size_b)
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

/*
 * The target position is determined by finding where the element from B
 * should be inserted in A to maintain sorted order.
 *
 * @param snapshot: Snapshot containing current state of both stacks
 * @param arena: Selector arena containing candidates array and metadata
 */
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
