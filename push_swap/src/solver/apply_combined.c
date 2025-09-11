
#include "../../include/solver.h"

/**
 * ApplyCombined applies a combined rotation and push operation based on the given position.
 * It performs common rotations (rr/rrr) first, then remaining rotations, and finally the push operation.
 * 
 * @param ps Pointer to the sorting state
 * @param p Position containing cost_a and cost_b values
 * @param push_to_b Boolean indicating whether to push to stack B (true) or A (false)
 */
void	apply_combined(t_sorting_state *ps, t_position p, bool push_to_b)
{
	int	a;
	int	b;

	a = p.cost_a;
	b = p.cost_b;
	// Common rotation - perform rr/rrr operations
	while (a > 0 && b > 0)
	{
		rotate_ab(ps);
		a--;
		b--;
	}
	while (a < 0 && b < 0)
	{
		reverse_rotate_ab(ps);
		a++;
		b++;
	}
	// Remaining rotations - perform individual rotations
	while (a > 0)
	{
		rotate_a(ps);
		a--;
	}
	while (a < 0)
	{
		reverse_rotate_a(ps);
		a++;
	}
	while (b > 0)
	{
		rotate_b(ps);
		b--;
	}
	while (b < 0)
	{
		reverse_rotate_b(ps);
		b++;
	}
	// Push operation
	if (push_to_b)
		push_b(ps);
	else
		push_a(ps);
}
