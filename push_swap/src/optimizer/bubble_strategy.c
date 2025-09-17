#include "../../include/optimizer.h"

t_operation	get_target_operation_for_a(t_operation a)
{
	if (a == RA)
		return (RB);
	return (RRB);
}

t_operation	get_target_operation_for_b(t_operation a)
{
	if (a == RB)
		return (RA);
	return (RRA);
}

bool	search_and_bubble_a(t_list *out, int i, int n, int max_gap, bool *changed)
{
	t_operation	a = get_operation_at_index(out, i);
	t_operation	want = get_target_operation_for_a(a);
	int			j = i + 1;

	while (j < n && j - i - 1 <= max_gap)
	{
		t_operation	op_j = get_operation_at_index(out, j);
		if (op_j == want)
		{
			if (bubble_operation(out, i, j, true))
				*changed = true;
			return (true);
		}
		if (is_barrier(op_j) || touches_a(op_j))
			break;
		j++;
	}
	return (false);
}

bool	search_and_bubble_b(t_list *out, int i, int n, int max_gap, bool *changed)
{
	t_operation	a = get_operation_at_index(out, i);
	t_operation	want = get_target_operation_for_b(a);
	int			j = i + 1;

	while (j < n && j - i - 1 <= max_gap)
	{
		t_operation	op_j = get_operation_at_index(out, j);
		if (op_j == want)
		{
			if (bubble_operation(out, i, j, false))
				*changed = true;
			return (true);
		}
		if (is_barrier(op_j) || touches_b(op_j))
			break;
		j++;
	}
	return (false);
}

void	process_operation_at_index(t_list *out, int i, int n, int max_gap, bool *changed)
{
	t_operation	a = get_operation_at_index(out, i);

	if (a == RA || a == RRA)
		search_and_bubble_a(out, i, n, max_gap, changed);
	else if (a == RB || a == RRB)
		search_and_bubble_b(out, i, n, max_gap, changed);
}
