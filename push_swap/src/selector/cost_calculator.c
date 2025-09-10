
#include "../../include/selector.h"

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
