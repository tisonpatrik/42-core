/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearbest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:03 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 21:41:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

// SelectBestBtoAMove selects the best position for moving an element from B to A using near-optimal strategy.
// It considers multiple candidates and uses micro-lookahead to make the best choice.
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
	// Snapshot stacks for efficient processing
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
	// Enumerate candidates from B to A
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
	// Filter and select best candidate using lookahead
	result = select_best_candidate_with_lookahead(a, size_a, b, size_b, 
		candidates, candidate_count, max_candidates, config, MOVE_B_TO_A);
	free(a);
	free(b);
	free(candidates);
	return (result);
}

// PickNearBest is kept for backward compatibility - delegates to SelectBestBtoAMove
t_position	pick_near_best(t_sorting_state *ps, int max_candidates)
{
	return (select_best_b_to_a_move(ps, max_candidates));
}

// SelectBestCandidateWithLookahead filters candidates and selects the best one using micro-lookahead
t_position	select_best_candidate_with_lookahead(int *a, int size_a, int *b, 
	int size_b, t_candidate *candidates, int count, int max_candidates, 
	t_selector_config config, t_move_direction direction)
{
	t_candidate			*filtered_candidates;
	int					filtered_count;
	t_candidate			*top_k_candidates;
	int					top_k_count;
	t_lookahead_evaluator	*evaluator;
	t_position			result;

	if (!a || !b || !candidates || count == 0)
	{
		result.total = INT_MAX;
		return (result);
	}
	// 1) Filter candidates by cost threshold
	filtered_candidates = filter_candidates_by_threshold(candidates, count, 
		config.cost_threshold_offset, &filtered_count);
	if (!filtered_candidates)
	{
		result.total = INT_MAX;
		return (result);
	}
	// 2) Select top-K candidates by score for further evaluation
	top_k_candidates = select_top_k_candidates(filtered_candidates, 
		filtered_count, max_candidates, &top_k_count);
	free(filtered_candidates);
	if (!top_k_candidates)
	{
		result.total = INT_MAX;
		return (result);
	}
	// 3) Evaluate candidates with micro-lookahead and select the best
	evaluator = new_lookahead_evaluator(config);
	if (!evaluator)
	{
		free(top_k_candidates);
		result.total = INT_MAX;
		return (result);
	}
	result = evaluate_with_lookahead(evaluator, a, size_a, b, size_b, 
		top_k_candidates, top_k_count, direction);
	free_lookahead_evaluator(evaluator);
	free(top_k_candidates);
	return (result);
}
