/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookahead_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/12 21:34:59 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>

static int	calculate_heuristic(t_stack *stack)
{
	t_node	*current;
	int		heuristic;
	int		prev_value;
	int		current_value;
	bool	first_iteration;

	if (!stack || get_size(stack) <= 1)
		return (0);
	heuristic = 0;
	current = get_head(stack);
	prev_value = get_content(current);
	current = get_next(current);
	first_iteration = true;
	while (current)
	{
		current_value = get_content(current);
		if (!first_iteration && current_value < prev_value)
			heuristic++;
		prev_value = current_value;
		current = get_next(current);
		first_iteration = false;
	}
	return (heuristic);
}

t_position	evaluate_with_lookahead(t_sorting_state *state, t_candidate *candidates, t_selector_arena *arena)
{
	t_position	best_position;
	int			i;
	int			heuristic_penalty;
	int			adjusted_score;
	int			count;


	count = arena->top_k_count;
	if (count == 0)
	{
		best_position.total = INT_MAX;
		return (best_position);
	}
	best_position = candidates[0].position;
	i = 1;
	while (i < count)
	{
		heuristic_penalty = calculate_heuristic(state->a) + calculate_heuristic(state->b);
		adjusted_score = candidates[i].position.total + heuristic_penalty;
		if (adjusted_score < best_position.total)
			best_position = candidates[i].position;
		i++;
	}
	return (best_position);
}