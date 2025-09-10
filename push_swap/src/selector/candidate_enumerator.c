
#include "../../include/selector.h"

// NewCandidateEnumerator creates a new CandidateEnumerator with the given configuration
t_candidate_enumerator	*new_candidate_enumerator(t_selector_config config)
{
	t_candidate_enumerator	*enumerator;

	enumerator = malloc(sizeof(t_candidate_enumerator));
	if (!enumerator)
		return (NULL);
	enumerator->cost_calc = new_cost_calculator(config);
	if (!enumerator->cost_calc)
	{
		free(enumerator);
		return (NULL);
	}
	enumerator->config = config;
	return (enumerator);
}

// FreeCandidateEnumerator frees the memory allocated for a CandidateEnumerator
void	free_candidate_enumerator(t_candidate_enumerator *enumerator)
{
	if (enumerator)
	{
		if (enumerator->cost_calc)
			free_cost_calculator(enumerator->cost_calc);
		free(enumerator);
	}
}

// EnumerateAtoB enumerates all possible positions for moving elements from stack A to stack B
t_candidate	*enumerate_a_to_b(t_candidate_enumerator *enumerator, 
	t_stack *a, t_stack *b, int *count)
{
	int			size_a;
	t_candidate	*candidates;
	int			candidate_count;
	t_candidate	*filtered;
	int			filtered_count;
	t_candidate	*result;

	if (!enumerator || !a || !b || !count)
		return (NULL);
	size_a = get_size(a);
	if (size_a == 0)
	{
		*count = 0;
		return (NULL);
	}
	// Build candidates from stack A
	candidates = build_candidates_from_stack_a(enumerator, a, b, &candidate_count);
	if (!candidates)
	{
		*count = 0;
		return (NULL);
	}
	// Filter candidates by cost threshold
	filtered = filter_candidates_by_threshold(candidates, candidate_count, 
		enumerator->config.cost_threshold_offset, &filtered_count);
	free(candidates);
	if (!filtered)
	{
		*count = 0;
		return (NULL);
	}
	// Return top K candidates (0 means all)
	result = select_top_k_candidates(filtered, filtered_count, 0, count);
	free(filtered);
	return (result);
}

// EnumerateBtoA enumerates all possible positions for moving elements from stack B to stack A
t_candidate	*enumerate_b_to_a(t_candidate_enumerator *enumerator, 
	int *a, int size_a, int *b, int size_b, int *count)
{
	t_candidate	*candidates;
	int			i;
	int			val;
	int			to_idx;
	int			cost_a;
	int			cost_b;
	int			base;
	t_position	position;

	if (!enumerator || !a || !b || !count)
		return (NULL);
	if (is_empty(b, size_b))
	{
		*count = 0;
		return (NULL);
	}
	candidates = malloc(sizeof(t_candidate) * size_b);
	if (!candidates)
		return (NULL);
	i = 0;
	while (i < size_b)
	{
		val = b[i];
		to_idx = find_target_position(a, size_a, val);
		// For BtoA moves: fromIdx=i (in stack B), toIdx=toIdx (in stack A)
		// CostA is calculated from toIdx and sizeA, CostB from fromIdx and sizeB
		cost_a = signed_cost(to_idx, size_a);
		cost_b = signed_cost(i, size_b);
		base = merged_cost(cost_a, cost_b);
		position.from_index = i; // index in stack B
		position.to_index = to_idx; // index in stack A
		position.cost_a = cost_a;
		position.cost_b = cost_b;
		position.total = base;
		candidates[i] = new_candidate(position, base);
		i++;
	}
	*count = size_b;
	return (candidates);
}

// BuildCandidatesFromStackA builds candidate positions by evaluating each element in stack A
t_candidate	*build_candidates_from_stack_a(t_candidate_enumerator *enumerator, 
	t_stack *a, t_stack *b, int *count)
{
	int			size_a;
	int			*bvals;
	int			bvals_size;
	t_candidate	*candidates;
	t_node		*current;
	int			i;
	int			val;
	int			to_idx;
	t_position	position;
	int			base;
	int			penalty;

	if (!enumerator || !a || !b || !count)
		return (NULL);
	size_a = get_size(a);
	if (size_a == 0)
	{
		*count = 0;
		return (NULL);
	}
	bvals = snapshot_stack(b, &bvals_size);
	if (!bvals)
	{
		*count = 0;
		return (NULL);
	}
	candidates = malloc(sizeof(t_candidate) * size_a);
	if (!candidates)
	{
		free(bvals);
		*count = 0;
		return (NULL);
	}
	current = get_head(a);
	i = 0;
	while (current != NULL)
	{
		val = get_content(current);
		to_idx = find_insertion_index(bvals, bvals_size, val);
		position = calculate_position_cost(enumerator->cost_calc, i, to_idx, 
			size_a, bvals_size);
		base = position.total;
		penalty = calculate_penalty(enumerator->cost_calc, bvals, bvals_size, 
			to_idx, val);
		candidates[i] = new_candidate(position, base + penalty);
		current = get_next(current);
		i++;
	}
	free(bvals);
	*count = size_a;
	return (candidates);
}
