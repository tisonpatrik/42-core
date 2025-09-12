/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearbest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:03 by patrik            #+#    #+#             */
/*   Updated: 2025/09/12 23:11:21 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"


t_position	find_best_move(t_sorting_state *state, t_move_direction direction,
	t_selector_arena *arena)
{
	t_candidate	*candidates;
	t_candidate	*filtered_candidates;
	t_candidate	*top_k_candidates;
	t_position	result;

	candidates = enumerate_candidates(state, direction, arena);

	filtered_candidates = build_filtered_candidates(candidates,
		arena->config.cost_threshold_offset, arena);

	top_k_candidates = build_top_k_candidates(filtered_candidates,
		arena->config.max_candidates, arena);

	result = evaluate_with_lookahead(state, top_k_candidates, arena);
	return (result);
}

t_position	select_best_a_to_b_move(t_sorting_state *ps, int max_candidates, t_simulation_config config)
{
	t_selector_arena	*arena;
	t_position		result;
	int			max_stack_size;

	max_stack_size = get_max_stack_size(ps->a, ps->b);
	arena = allocate_selector_arena(max_candidates, max_stack_size);
	if (!arena)
	{
		result.total = INT_MAX;
		return (result);
	}
	arena->config = config;
	result = find_best_move(ps, MOVE_A_TO_B, arena);
	free_selector_arena(arena);
	return (result);
}

t_position	select_best_b_to_a_move(t_sorting_state *ps, int max_candidates, t_simulation_config config)
{
	t_selector_arena	*arena;
	t_position		result;
	int			max_stack_size;

	max_stack_size = (get_size(ps->a) > get_size(ps->b)) ? get_size(ps->a) : get_size(ps->b);
	arena = allocate_selector_arena(max_candidates, max_stack_size);
	if (!arena)
	{
		result.total = INT_MAX;
		return (result);
	}
	arena->config = config;
	arena->config.max_candidates = max_candidates;
	result = find_best_move(ps, MOVE_B_TO_A, arena);
	free_selector_arena(arena);
	return (result);
}
