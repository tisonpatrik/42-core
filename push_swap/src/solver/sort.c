/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:21 by ptison            #+#    #+#             */
/*   Updated: 2025/09/15 00:01:46 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/separator.h"
#include "../../include/stack.h"
#include "../../include/selector.h"
#include "../../include/optimizer.h"
#include "../../include/solver.h"
#include "../../include/simulation_config.h"
#include "../../libft/include/list.h"
#include <stdio.h>

void	solve_push_swap(t_sorting_state *state)
{
	if (is_sorted(state->a))
		return ;
	
	push_non_lis_into_b(state);

	t_simulation_config config = default_selector_config();

	int max_candidates = 30;
	while (get_size(state->a) > 3)
	{
		t_position position =select_best_b_to_a_move (state, max_candidates, config);
		apply_combined(state, position, true);
	}

	printf("Before sort_three - Stack A and B values:\n");
	print_state_values(state);
	
	sort_three(state);

	while (get_size(state->b) > 0)
	{
		t_position position = select_best_a_to_b_move(state, max_candidates, config);
		apply_combined(state, position, false); // pa
	}
 
	// align_min_to_top(state);

	// state->operations = optimize_ops(state->operations);
}
