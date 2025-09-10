/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:12 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:59:22 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

t_position	select_best_a_to_b_move(t_sorting_state *ps)
{
	t_candidate_enumerator	*enumerator;
	t_candidate				*candidates;
	int						count;
	t_position				best;

	if (!ps)
	{
		best.total = INT_MAX;
		return (best);
	}
	enumerator = new_candidate_enumerator(default_selector_config());
	if (!enumerator)
	{
		best.total = INT_MAX;
		return (best);
	}
	candidates = enumerate_a_to_b(enumerator, ps->a, ps->b, &count);
	if (!candidates)
	{
		free_candidate_enumerator(enumerator);
		best.total = INT_MAX;
		return (best);
	}
	best = select_best_candidate(candidates, count);
	free(candidates);
	free_candidate_enumerator(enumerator);
	return (best);
}
