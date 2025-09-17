#include "../../include/optimizer.h"

t_operation	get_absorption_result_rr_rra(t_operation a)
{
	if (a == RR)
		return (RB);
	return (RRB);
}

t_operation	get_absorption_result_rr_rrb(t_operation a)
{
	if (a == RR)
		return (RA);
	return (RRA);
}

t_operation	get_absorption_result_rrr_ra(t_operation a)
{
	if (a == RRR)
		return (RRB);
	return (RB);
}

t_operation	get_absorption_result_rrr_rb(t_operation a)
{
	if (a == RRR)
		return (RRA);
	return (RA);
}

bool	try_merge_operations(t_operation a, t_operation b, t_list **dst, t_list **current)
{
	if (try_merge_rotate_pairs(a, b, dst, current))
		return (true);
	if (try_merge_swap_pairs(a, b, dst, current))
		return (true);
	if (try_merge_absorption_cases(a, b, dst, current))
		return (true);
	return (false);
}
