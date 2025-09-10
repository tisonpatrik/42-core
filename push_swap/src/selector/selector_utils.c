/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/01/27 00:00:00 by patrik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"

// DefaultSelectorConfig returns the default configuration for the selector
t_selector_config	default_selector_config(void)
{
	t_selector_config	config;

	config.max_candidates = 30;
	config.cost_threshold_offset = 1;
	config.size_penalty_factor = 10;
	config.heuristic_offset = 1;
	config.heuristic_divisor = 2;
	return (config);
}

// NewCostCalculator creates a new CostCalculator with the given configuration
t_cost_calculator	*new_cost_calculator(t_selector_config config)
{
	t_cost_calculator	*calc;

	calc = malloc(sizeof(t_cost_calculator));
	if (!calc)
		return (NULL);
	calc->config = config;
	return (calc);
}

// FreeCostCalculator frees the memory allocated for a CostCalculator
void	free_cost_calculator(t_cost_calculator *calc)
{
	if (calc)
		free(calc);
}

// CalculatePositionCost calculates the complete cost for moving an element
// from fromIdx to toIdx between stacks of given sizes
t_position	calculate_position_cost(t_cost_calculator *calc, int from_idx, 
	int to_idx, int size_a, int size_b)
{
	t_position	position;
	int			cost_a;
	int			cost_b;
	int			base;

	cost_a = signed_cost(from_idx, size_a);
	cost_b = signed_cost(to_idx, size_b);
	base = calculate_merged_cost(calc, cost_a, cost_b);
	position.from_index = from_idx;
	position.to_index = to_idx;
	position.cost_a = cost_a;
	position.cost_b = cost_b;
	position.total = base;
	return (position);
}

// CalculatePenalty calculates penalty for local order violation in stack B
int	calculate_penalty(t_cost_calculator *calc, int *stack, int size, 
	int to_idx, int val)
{
	int	n;
	int	prev;
	int	next;

	(void)calc; // Unused parameter
	if (is_empty_or_single(stack, size))
		return (0);
	n = size;
	prev = stack[(to_idx - 1 + n) % n];
	next = stack[to_idx % n];
	if (prev > val && val > next)
		return (0);
	return (1);
}

// CalculateMergedCost calculates the total cost when combining two operations,
// accounting for common rotations (rr/rrr)
int	calculate_merged_cost(t_cost_calculator *calc, int cost_a, int cost_b)
{
	(void)calc; // Unused parameter
	return (merged_cost(cost_a, cost_b));
}

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

// NewMoveSimulator creates a new MoveSimulator
t_move_simulator	*new_move_simulator(void)
{
	t_move_simulator	*simulator;

	simulator = malloc(sizeof(t_move_simulator));
	if (!simulator)
		return (NULL);
	return (simulator);
}

// FreeMoveSimulator frees the memory allocated for a MoveSimulator
void	free_move_simulator(t_move_simulator *simulator)
{
	if (simulator)
		free(simulator);
}

// SimulateMove simulates a single move and returns the resulting stacks and cost
int	simulate_move(t_move_simulator *simulator, int *a, int size_a, 
	int *b, int size_b, t_position pos, t_move_direction direction, 
	int **new_a, int **new_b)
{
	int	rot;
	int	ia;
	int	ib;
	int	x;
	int	new_a_size;
	int	new_b_size;

	(void)simulator; // Unused parameter
	rot = merged_cost(pos.cost_a, pos.cost_b); // actual rotations
	if (direction == MOVE_A_TO_B)
	{
		ia = normalize_index(size_a, pos.cost_a);
		ib = normalize_index(size_b, pos.cost_b);
		x = a[ia];
		*new_a = remove_element_at(a, size_a, ia, &new_a_size);
		if (!*new_a)
			return (INT_MAX);
		*new_b = insert_element_at(b, size_b, ib, x, &new_b_size);
		if (!*new_b)
		{
			free(*new_a);
			return (INT_MAX);
		}
		return (rot + 1);
	}
	// BtoA direction
	ib = normalize_index(size_b, pos.cost_b);
	ia = normalize_index(size_a, pos.cost_a);
	x = b[ib];
	*new_b = remove_element_at(b, size_b, ib, &new_b_size);
	if (!*new_b)
		return (INT_MAX);
	*new_a = insert_element_at(a, size_a, ia, x, &new_a_size);
	if (!*new_a)
	{
		free(*new_b);
		return (INT_MAX);
	}
	return (rot + 1);
}

// NewLookaheadEvaluator creates a new LookaheadEvaluator with the given configuration
t_lookahead_evaluator	*new_lookahead_evaluator(t_selector_config config)
{
	t_lookahead_evaluator	*evaluator;

	evaluator = malloc(sizeof(t_lookahead_evaluator));
	if (!evaluator)
		return (NULL);
	evaluator->simulator = new_move_simulator();
	if (!evaluator->simulator)
	{
		free(evaluator);
		return (NULL);
	}
	evaluator->config = config;
	return (evaluator);
}

// FreeLookaheadEvaluator frees the memory allocated for a LookaheadEvaluator
void	free_lookahead_evaluator(t_lookahead_evaluator *evaluator)
{
	if (evaluator)
	{
		if (evaluator->simulator)
			free_move_simulator(evaluator->simulator);
		free(evaluator);
	}
}

// EvaluateWithLookahead performs micro-lookahead evaluation (depth 1) on candidates
t_position	evaluate_with_lookahead(t_lookahead_evaluator *evaluator, 
	int *a, int size_a, int *b, int size_b, t_candidate *candidates, 
	int count, t_move_direction direction)
{
	t_position	best_position;
	int			best_score;
	int			i;
	int			actual_cost;
	int			heuristic_estimate;
	int			total_score;
	int			*new_a;
	int			*new_b;

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
		// Simulate the move and get the actual cost (g)
		actual_cost = simulate_move(evaluator->simulator, a, size_a, b, size_b, 
			candidates[i].position, direction, &new_a, &new_b);
		if (actual_cost == INT_MAX)
		{
			i++;
			continue;
		}
		// Calculate heuristic estimate of remaining work (h)
		heuristic_estimate = calculate_heuristic(evaluator, new_a, size_a);
		// Combined score = actual cost + heuristic estimate
		total_score = actual_cost + heuristic_estimate;
		// Select better position (lower score, or same score with better position)
		if (total_score < best_score || (total_score == best_score && 
			better_position(candidates[i].position, best_position)))
		{
			best_position = candidates[i].position;
			best_score = total_score;
		}
		free(new_a);
		free(new_b);
		i++;
	}
	return (best_position);
}

// CalculateHeuristic calculates a heuristic estimate of remaining work
int	calculate_heuristic(t_lookahead_evaluator *evaluator, int *stack, int size)
{
	int	breakpoints;
	int	size_penalty;

	if (!evaluator || !stack)
		return (0);
	// Using breakpoints and size penalty as a cheap heuristic for stack disorder
	breakpoints = calculate_breakpoints(stack, size);
	size_penalty = size / evaluator->config.size_penalty_factor;
	return ((breakpoints + size_penalty + evaluator->config.heuristic_offset) / 
		evaluator->config.heuristic_divisor);
}

// BetterPosition compares two positions and returns true if the first position is better than the second
bool	better_position(t_position a, t_position b)
{
	if (a.total != b.total)
		return (a.total < b.total);
	if (ft_abs(a.cost_a) != ft_abs(b.cost_a))
		return (ft_abs(a.cost_a) < ft_abs(b.cost_a));
	if (a.to_index != b.to_index)
		return (a.to_index < b.to_index);
	return (a.from_index < b.from_index);
}

// NewCandidate creates a new Candidate with the given position and score
t_candidate	new_candidate(t_position pos, int score)
{
	t_candidate	candidate;

	candidate.position = pos;
	candidate.score = score;
	return (candidate);
}

// FilterCandidatesByThreshold filters candidates to keep only those within the cost threshold
t_candidate	*filter_candidates_by_threshold(t_candidate *candidates, 
	int count, int threshold_offset, int *filtered_count)
{
	int			min_base_cost;
	int			threshold;
	t_candidate	*filtered;
	int			i;
	int			j;

	if (count == 0)
	{
		*filtered_count = 0;
		return (NULL);
	}
	// Find minimum base cost
	min_base_cost = INT_MAX;
	i = 0;
	while (i < count)
	{
		if (candidates[i].position.total < min_base_cost)
			min_base_cost = candidates[i].position.total;
		i++;
	}
	// Filter by threshold
	threshold = min_base_cost + threshold_offset;
	filtered = malloc(sizeof(t_candidate) * count);
	if (!filtered)
		return (NULL);
	j = 0;
	i = 0;
	while (i < count)
	{
		if (candidates[i].position.total <= threshold)
		{
			filtered[j] = candidates[i];
			j++;
		}
		i++;
	}
	*filtered_count = j;
	return (filtered);
}

// Compare function for sorting candidates
static int	compare_candidates(const void *a, const void *b)
{
	const t_candidate	*candidate_a = (const t_candidate *)a;
	const t_candidate	*candidate_b = (const t_candidate *)b;

	if (candidate_a->score != candidate_b->score)
		return (candidate_a->score - candidate_b->score);
	// Use BetterPosition for tie-breakers
	if (better_position(candidate_a->position, candidate_b->position))
		return (-1);
	return (1);
}

// SelectTopKCandidates sorts candidates by score and returns the top K candidates
t_candidate	*select_top_k_candidates(t_candidate *candidates, 
	int count, int max_k, int *result_count)
{
	t_candidate	*sorted;
	int			result_size;

	if (count == 0)
	{
		*result_count = 0;
		return (NULL);
	}
	sorted = malloc(sizeof(t_candidate) * count);
	if (!sorted)
		return (NULL);
	ft_memcpy(sorted, candidates, sizeof(t_candidate) * count);
	// Sort by score with tie-breakers
	qsort(sorted, count, sizeof(t_candidate), compare_candidates);
	// Limit to top K candidates if specified
	if (max_k > 0 && max_k < count)
		result_size = max_k;
	else
		result_size = count;
	*result_count = result_size;
	return (sorted);
}

// SelectBestCandidate selects the best candidate from a list of candidates
t_position	select_best_candidate(t_candidate *candidates, int count)
{
	t_position	best;
	int			i;

	if (count == 0)
	{
		best.total = INT_MAX;
		return (best);
	}
	best = candidates[0].position;
	i = 1;
	while (i < count)
	{
		if (better_position(candidates[i].position, best))
			best = candidates[i].position;
		i++;
	}
	return (best);
}

// MergedCost calculates the total cost when combining two operations,
// accounting for common rotations (rr/rrr)
int	merged_cost(int a, int b)
{
	bool	same;

	same = (a >= 0 && b >= 0) || (a < 0 && b < 0);
	if (same)
	{
		if (ft_abs(a) > ft_abs(b))
			return (ft_abs(a));
		return (ft_abs(b));
	}
	return (ft_abs(a) + ft_abs(b));
}

// SignedCost calculates the signed cost (positive for rotate, negative for reverse rotate)
// to move an element to a specific index
int	signed_cost(int idx, int size)
{
	if (idx <= size / 2)
		return (idx);
	return (idx - size);
}

// IsEmpty returns true if the array is empty
bool	is_empty(int *arr, int size)
{
	(void)arr;
	return (size == 0);
}

// IsEmptyOrSingle returns true if the array has 0 or 1 elements
bool	is_empty_or_single(int *arr, int size)
{
	(void)arr;
	return (size <= 1);
}

// RemoveElementAt removes an element at the specified index from an array
int	*remove_element_at(int *arr, int size, int index, int *new_size)
{
	int	*result;
	int	i;
	int	j;

	if (index < 0 || index >= size)
	{
		*new_size = size;
		return (NULL);
	}
	result = malloc(sizeof(int) * (size - 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i != index)
		{
			result[j] = arr[i];
			j++;
		}
		i++;
	}
	*new_size = size - 1;
	return (result);
}

// InsertElementAt inserts an element at the specified index into an array
int	*insert_element_at(int *arr, int size, int index, int value, int *new_size)
{
	int	*result;
	int	i;

	if (index < 0 || index > size)
	{
		*new_size = size;
		return (NULL);
	}
	result = malloc(sizeof(int) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < index)
	{
		result[i] = arr[i];
		i++;
	}
	result[i] = value;
	i++;
	while (i <= size)
	{
		result[i] = arr[i - 1];
		i++;
	}
	*new_size = size + 1;
	return (result);
}

// SnapshotStack converts a stack to an array representation for efficient processing
int	*snapshot_stack(t_stack *stack, int *size)
{
	int		*result;
	t_node	*current;
	int		i;

	*size = get_size(stack);
	if (*size == 0)
		return (NULL);
	result = malloc(sizeof(int) * *size);
	if (!result)
		return (NULL);
	current = get_head(stack);
	i = 0;
	while (current != NULL)
	{
		result[i] = get_content(current);
		current = get_next(current);
		i++;
	}
	return (result);
}

// CalculateBreakpoints calculates the number of breakpoints in a cyclic array
int	calculate_breakpoints(int *arr, int size)
{
	int	breakpoints;
	int	i;

	if (is_empty_or_single(arr, size))
		return (0);
	breakpoints = 0;
	i = 0;
	while (i < size - 1)
	{
		if (arr[i] > arr[i + 1])
			breakpoints++;
		i++;
	}
	if (arr[size - 1] > arr[0])
		breakpoints++;
	return (breakpoints);
}

// Helper comparator functions for binary search
static bool	less_than(int arr_val, int target_val)
{
	return (arr_val < target_val);
}

static bool	less_than_or_equal(int arr_val, int target_val)
{
	return (arr_val <= target_val);
}

// BinarySearchInsertionPoint performs binary search to find insertion point for a value
// using a custom comparator function
int	binary_search_insertion_point(int *arr, int size, int val, 
	bool (*comparator)(int, int))
{
	int	left;
	int	right;
	int	mid;

	if (size == 0)
		return (0);
	left = 0;
	right = size;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (comparator(arr[mid], val))
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

// FindInsertionIndex finds the insertion index in a sorted descending array (stack B)
// maintaining local order "prev > val > next"
int	find_insertion_index(int *sorted_arr, int size, int val)
{
	int	idx;
	int	n;
	int	prev;
	int	next;
	int	j;

	if (is_empty(sorted_arr, size))
		return (0);
	// Binary search for insertion point in sorted descending array
	idx = binary_search_insertion_point(sorted_arr, size, val, less_than);
	n = size;
	idx = idx % n;
	// Check circular neighbors for proper local order
	prev = sorted_arr[(idx - 1 + n) % n];
	next = sorted_arr[idx % n];
	if (prev > val && val > next)
		return (idx);
	// Fallback to linear search if binary search doesn't find exact position
	j = 0;
	while (j < n)
	{
		prev = sorted_arr[(j - 1 + n) % n];
		next = sorted_arr[j];
		if (prev > val && val > next)
			return (j);
		j++;
	}
	return (0);
}

// FindTargetPosition finds the target position in a sorted ascending array (stack A)
// for inserting a value to maintain ascending order
int	find_target_position(int *sorted_arr, int size, int val)
{
	int	idx;
	int	n;

	if (is_empty(sorted_arr, size))
		return (0);
	// Binary search for the first element > val
	idx = binary_search_insertion_point(sorted_arr, size, val, less_than_or_equal);
	n = size;
	if (idx < n)
		return (idx);
	// If val >= all elements, return index of minimum (0 in sorted ascending stack)
	return (0);
}

// NormalizeIndex normalizes an index to be within bounds [0, n)
int	normalize_index(int n, int k)
{
	if (n == 0)
		return (0);
	k = ((k % n) + n) % n;
	return (k);
}

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

// ft_abs returns the absolute value of an integer
int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
