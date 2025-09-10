/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearbest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:03 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:37:49 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"


t_position	select_best_b_to_a_move(t_sorting_state *ps, int max_candidates)
{
	t_selector_config	config;
	int					*a;
	int					*b;
	int					size_a;
	int					size_b;
	t_candidate_enumerator	*enumerator;
	t_candidate			*candidates;
	int					candidate_count;
	t_position			result;

	if (!ps)
	{
		result.total = INT_MAX;
		return (result);
	}
	config = default_selector_config();
	a = snapshot_stack(ps->a, &size_a);
	b = snapshot_stack(ps->b, &size_b);
	if (!a || !b)
	{
		if (a)
			free(a);
		if (b)
			free(b);
		result.total = INT_MAX;
		return (result);
	}
	enumerator = new_candidate_enumerator(config);
	if (!enumerator)
	{
		free(a);
		free(b);
		result.total = INT_MAX;
		return (result);
	}
	candidates = enumerate_b_to_a(enumerator, a, size_a, b, size_b, &candidate_count);
	free_candidate_enumerator(enumerator);
	if (!candidates || candidate_count == 0)
	{
		free(a);
		free(b);
		if (candidates)
			free(candidates);
		return (select_best_a_to_b_move(ps));
	}
	result = select_best_candidate_with_lookahead(ps->a, ps->b, 
		candidates, candidate_count, max_candidates, config, MOVE_B_TO_A);
	free(a);
	free(b);
	free(candidates);
	return (result);
}

t_position	pick_near_best(t_sorting_state *ps, int max_candidates)
{
	return (select_best_b_to_a_move(ps, max_candidates));
}

t_position	select_best_candidate_with_lookahead(t_stack *stack_a, t_stack *stack_b, 
	t_candidate *candidates, int count, int max_candidates, 
	t_selector_config config, t_move_direction direction)
{
	t_candidate			*filtered_candidates;
	int					filtered_count;
	t_candidate			*top_k_candidates;
	int					top_k_count;
	t_lookahead_evaluator	*evaluator;
	t_position			result;

	if (!stack_a || !stack_b || !candidates || count == 0)
	{
		result.total = INT_MAX;
		return (result);
	}
	filtered_candidates = filter_candidates_by_threshold(candidates, count, 
		config.cost_threshold_offset, &filtered_count);
	if (!filtered_candidates)
	{
		result.total = INT_MAX;
		return (result);
	}
	top_k_candidates = select_top_k_candidates(filtered_candidates, 
		filtered_count, max_candidates, &top_k_count);
	free(filtered_candidates);
	if (!top_k_candidates)
	{
		result.total = INT_MAX;
		return (result);
	}
	evaluator = new_lookahead_evaluator(config);
	if (!evaluator)
	{
		free(top_k_candidates);
		result.total = INT_MAX;
		return (result);
	}
	result = evaluate_with_lookahead(evaluator, stack_a, stack_b, 
		top_k_candidates, top_k_count, direction);
	free_lookahead_evaluator(evaluator);
	free(top_k_candidates);
	return (result);
}
