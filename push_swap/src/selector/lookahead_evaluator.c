/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookahead_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:09 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:59:22 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

t_lookahead_evaluator	*new_lookahead_evaluator(t_selector_config config)
{
	t_lookahead_evaluator	*evaluator;

	evaluator = malloc(sizeof(t_lookahead_evaluator));
	if (!evaluator)
		return (NULL);
	evaluator->config = config;
	return (evaluator);
}

void	free_lookahead_evaluator(t_lookahead_evaluator *evaluator)
{
	if (evaluator)
		free(evaluator);
}

static int	simulate_move_cost(t_stack *stack_a, t_stack *stack_b, 
	t_position position, t_move_direction direction);

t_position	evaluate_with_lookahead(t_lookahead_evaluator *evaluator, 
	t_stack *stack_a, t_stack *stack_b, t_candidate *candidates, 
	int count, t_move_direction direction)
{
	t_position	best_position;
	int			best_score;
	int			i;
	int			actual_cost;
	int			heuristic_estimate;
	int			total_score;

	if (!evaluator || !candidates || count == 0)
	{
		best_position.total = INT_MAX;
		return (best_position);
	}
	best_position = candidates[0].position;
	best_score = INT_MAX;
	i = 0;
	while (i < count)
	{
		actual_cost = simulate_move_cost(stack_a, stack_b, 
			candidates[i].position, direction);
		if (actual_cost == INT_MAX)
		{
			i++;
			continue;
		}
		heuristic_estimate = calculate_heuristic(evaluator, stack_a);
		total_score = actual_cost + heuristic_estimate;
		if (total_score < best_score || (total_score == best_score && 
			better_position(candidates[i].position, best_position)))
		{
			best_position = candidates[i].position;
			best_score = total_score;
		}
		i++;
	}
	return (best_position);
}

static int	simulate_move_cost(t_stack *stack_a, t_stack *stack_b, 
	t_position position, t_move_direction direction)
{
	(void)stack_a;
	(void)stack_b;
	(void)direction;
	return (position.total + 1);
}

int	calculate_heuristic(t_lookahead_evaluator *evaluator, t_stack *stack)
{
	int	breakpoints;
	int	size_penalty;
	int	*stack_array;
	int	size;

	if (!evaluator || !stack)
		return (0);
	stack_array = snapshot_stack(stack, &size);
	if (!stack_array)
		return (0);
	breakpoints = calculate_breakpoints(stack_array, size);
	size_penalty = size / evaluator->config.size_penalty_factor;
	free(stack_array);
	return ((breakpoints + size_penalty + evaluator->config.heuristic_offset) / 
		evaluator->config.heuristic_divisor);
}
