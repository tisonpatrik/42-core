
#include "../../include/selector.h"

// SelectBestAtoBMove finds the position with the lowest cost for moving an element from stack A to stack B.
// It evaluates all possible positions and returns the one with minimal rotation cost.
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

// CheapestAtoB is kept for backward compatibility - delegates to SelectBestAtoBMove
t_position	cheapest_a_to_b(t_sorting_state *ps)
{
	return (select_best_a_to_b_move(ps));
}
