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
	if ((a == RA && b == RB) || (a == RB && b == RA))
	{
		add_operation_to_list(dst, RR);
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RRA && b == RRB) || (a == RRB && b == RRA))
	{
		add_operation_to_list(dst, RRR);
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == SA && b == SB) || (a == SB && b == SA))
	{
		add_operation_to_list(dst, SS);
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RR && b == RRA) || (a == RRA && b == RR))
	{
		add_operation_to_list(dst, get_absorption_result_rr_rra(a));
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RR && b == RRB) || (a == RRB && b == RR))
	{
		add_operation_to_list(dst, get_absorption_result_rr_rrb(a));
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RRR && b == RA) || (a == RA && b == RRR))
	{
		add_operation_to_list(dst, get_absorption_result_rrr_ra(a));
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RRR && b == RB) || (a == RB && b == RRR))
	{
		add_operation_to_list(dst, get_absorption_result_rrr_rb(a));
		*current = (*current)->next->next;
		return (true);
	}
	return (false);
}
