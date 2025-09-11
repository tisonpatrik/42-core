#include "../../include/solver.h"
#include "../../include/selector.h"

/**
 * AlignMinToTop rotates stack A to bring the minimum element to the top via the shortest path.
 * This is the final step in the push_swap algorithm to ensure proper ordering.
 * 
 * @param ps Pointer to the sorting state
 */
void	align_min_to_top(t_sorting_state *ps)
{
	int		size_a;
	int		min_idx;
	int		min_val;
	int		cost;
	int		i;
	t_node	*n;

	size_a = get_size(ps->a);
	if (size_a == 0)
		return ;
	min_idx = 0;
	min_val = get_content(get_head(ps->a));
	n = get_head(ps->a);
	i = 0;
	while (n != NULL)
	{
		if (get_content(n) < min_val)
		{
			min_val = get_content(n);
			min_idx = i;
		}
		n = get_next(n);
		i++;
	}
	cost = signed_cost(min_idx, size_a);
	while (cost > 0)
	{
		rotate_a(ps);
		cost--;
	}
	while (cost < 0)
	{
		reverse_rotate_a(ps);
		cost++;
	}
}
