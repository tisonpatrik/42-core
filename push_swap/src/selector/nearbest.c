/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearbest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:03 by patrik            #+#    #+#             */
/*   Updated: 2025/09/17 22:21:59 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

t_position	find_best_move(t_sorting_state *state, t_selector_arena *arena)
{
	t_candidate	*candidates;
	t_candidate	*filtered_candidates;
	t_candidate	*top_k_candidates;
	t_position	result;

	candidates = enumerate_candidates(state, arena);
	filtered_candidates = build_filtered_candidates(candidates,
			arena->config.cost_threshold_offset, arena);
	top_k_candidates = build_top_k_candidates(filtered_candidates,
			arena->config.max_candidates, arena);
	result = evaluate_with_lookahead(top_k_candidates, arena);
	return (result);
}

t_position	select_best_move(t_sorting_state *ps, int max_candidates,
		t_simulation_config config)
{
	t_selector_arena	*arena;
	t_position			result;

	arena = allocate_selector_arena(ps->b->size, ps->len_of_inputs);
	if (!arena)
	{
		result.total = INT_MAX;
		return (result);
	}
	arena->config = config;
	arena->config.max_candidates = max_candidates;
	result = find_best_move(ps, arena);
	free_selector_arena(arena);
	return (result);
}
