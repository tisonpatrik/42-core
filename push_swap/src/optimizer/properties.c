/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:48:57 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 11:34:22 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

/*
 * Checks if an operation affects stack A.
 * @param op: Operation to check
 * @return: True if operation affects stack A, false otherwise
 */
bool	touches_a(t_operation op)
{
	if (op == SA || op == RA || op == RRA)
		return (true);
	return (false);
}

/*
 * Checks if an operation affects stack B.
 * @param op: Operation to check
 * @return: True if operation affects stack B, false otherwise
 */
bool	touches_b(t_operation op)
{
	if (op == SB || op == RB || op == RRB)
		return (true);
	return (false);
}

/*
 * Checks if an operation acts as a barrier for optimization.
 *
 * This function identifies operations that prevent certain
 * optimizations from being applied. Barrier operations include:
 * - SS: swap both stacks (affects both stacks simultaneously)
 * - RR: rotate both stacks (affects both stacks simultaneously)
 * - RRR: reverse rotate both stacks (affects both stacks simultaneously)
 * - PA: push from B to A (changes stack sizes)
 * - PB: push from A to B (changes stack sizes)
 *
 * @param op: Operation to check
 * @return: True if operation is a barrier, false otherwise
 */
bool	is_barrier(t_operation op)
{
	if (op == SS || op == RR || op == RRR || op == PA || op == PB)
		return (true);
	return (false);
}

/*
 * Checks if an operation is a pure stack A operation.
 * @param op: Operation to check
 * @return: True if operation only affects stack A, false otherwise
 */
bool	is_pure_a(t_operation op)
{
	return (op == SA || op == RA || op == RRA);
}

/*
 * Checks if an operation is a pure stack B operation.
 * @param op: Operation to check
 * @return: True if operation only affects stack B, false otherwise
 */
bool	is_pure_b(t_operation op)
{
	return (op == SB || op == RB || op == RRB);
}
