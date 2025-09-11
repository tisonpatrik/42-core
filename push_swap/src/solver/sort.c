/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:21 by ptison            #+#    #+#             */
/*   Updated: 2025/09/11 23:03:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/separator.h"
#include "../../include/stack.h"
#include "../../include/selector.h"
#include "../../include/optimizer.h"
#include "../../include/solver.h"
#include "../../libft/include/list.h"

void	solve_push_swap(t_sorting_state *state)
{
	if (is_sorted(state->a))
		return ;
	
	push_non_lis_into_b(state);

	while (get_size(state->a) > 3)
	{
		t_position position = select_best_a_to_b_move(state);
		apply_combined(state, position, true);
	}

	// sort_three(state);

	// while (get_size(state->b) > 0)
	// {
	// 	t_position position = select_best_b_to_a_move(state, candidate_count);
	// 	apply_combined(state, position, false); // pa
	// }
 
	// align_min_to_top(state);

	// state->operations = optimize_ops(state->operations);
}
