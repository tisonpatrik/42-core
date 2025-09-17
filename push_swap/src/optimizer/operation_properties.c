
#include "../../include/optimizer.h"


bool	touches_a(t_operation op)
{
	if (op == SA || op == RA || op == RRA)
		return (true);
	return (false);
}


bool	touches_b(t_operation op)
{
	if (op == SB || op == RB || op == RRB)
		return (true);
	return (false);
}

bool	is_barrier(t_operation op)
{
	if (op == SS || op == RR || op == RRR || op == PA || op == PB)
		return (true);
	return (false);
}


bool	is_pure_a(t_operation op)
{
	return (op == SA || op == RA || op == RRA);
}

bool	is_pure_b(t_operation op)
{
	return (op == SB || op == RB || op == RRB);
}
