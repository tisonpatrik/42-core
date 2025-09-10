
#include "../../include/selector.h"

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
