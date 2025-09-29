/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:21 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 22:13:07 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/solver.h"

bool	solve_push_swap(t_sorting_state *state)
{
	t_position	position;

	if (is_sorted(state->a))
		return (true);
	push_non_lis_into_b(state);
	while (get_size(state->a) > 3)
	{
		position = select_best_move(state);
		if (!position.is_valid)
			return (false);
		apply_combined(state, position, true);
	}
	sort_three(state);
	while (get_size(state->b) > 0)
	{
		position = select_best_move(state);
		if (!position.is_valid)
			return (false);
		apply_combined(state, position, false);
	}
	align_min_to_top(state);
	optimize_ops(&state->operations);
	return (true);
}
