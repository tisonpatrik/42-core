/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:21 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 21:55:59 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/optimizer.h"
#include "../../include/selector.h"
#include "../../include/separator.h"
#include "../../include/simulation_config.h"
#include "../../include/solver.h"
#include "../../include/stack.h"

void	solve_push_swap(t_sorting_state *state)
{
	t_simulation_config	config;
	int					max_candidates;
	t_position			position;

	if (is_sorted(state->a))
		return ;
	push_non_lis_into_b(state);
	config = default_selector_config();
	max_candidates = 30;
	while (get_size(state->a) > 3)
	{
		position = select_best_move(state, max_candidates, config);
		apply_combined(state, position, true);
	}
	sort_three(state);
	while (get_size(state->b) > 0)
	{
		position = select_best_move(state, max_candidates, config);
		apply_combined(state, position, false);
	}
	align_min_to_top(state);
	optimize_ops(&state->operations);
}
