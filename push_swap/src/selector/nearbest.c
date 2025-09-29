/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearbest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:03 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 22:08:47 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

static t_position	find_best_move(t_sorting_state *state,
		t_selector_arena *arena)
{
	t_position	result;

	if (!enumerate_candidates(state, arena))
	{
		return (create_invalid_position());
	}
	if (!build_filtered_candidates(arena->candidates,
			arena->config.cost_threshold_offset, arena))
	{
		return (create_invalid_position());
	}
	if (!build_top_k_candidates(arena->filtered_candidates,
			arena->config.max_candidates, arena))
	{
		return (create_invalid_position());
	}
	result = evaluate_with_lookahead(arena->top_k_candidates, arena);
	return (result);
}

t_position	select_best_move(t_sorting_state *ps)
{
	t_selector_arena	*arena;
	t_position			result;
	t_simulation_config	config;

	config = default_selector_config();
	arena = allocate_arena(ps->b->size, ps->len_of_inputs);
	if (!arena)
	{
		return (create_invalid_position());
	}
	arena->config = config;
	result = find_best_move(ps, arena);
	free_selector_arena(arena);
	return (result);
}
