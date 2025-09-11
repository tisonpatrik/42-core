#include "../../include/optimizer.h"

/**
 * Check if operation touches stack A
 * @param op Operation to check
 * @return true if operation affects stack A
 */
bool	touches_a(t_operation op)
{
	switch (op)
	{
		case SA:
		case RA:
		case RRA:
			return (true);
		default:
			return (false);
	}
}

/**
 * Check if operation touches stack B
 * @param op Operation to check
 * @return true if operation affects stack B
 */
bool	touches_b(t_operation op)
{
	switch (op)
	{
		case SB:
		case RB:
		case RRB:
			return (true);
		default:
			return (false);
	}
}

/**
 * Check if operation is a barrier (cannot be crossed during bubbling)
 * @param op Operation to check
 * @return true if operation is a barrier
 */
bool	is_barrier(t_operation op)
{
	switch (op)
	{
		case SS:
		case RR:
		case RRR:
		case PA:
		case PB:
			return (true);
		default:
			return (false);
	}
}

/**
 * Check if operation is purely A-only
 * @param op Operation to check
 * @return true if operation only affects stack A
 */
bool	is_pure_a(t_operation op)
{
	return (op == SA || op == RA || op == RRA);
}

/**
 * Check if operation is purely B-only
 * @param op Operation to check
 * @return true if operation only affects stack B
 */
bool	is_pure_b(t_operation op)
{
	return (op == SB || op == RB || op == RRB);
}
