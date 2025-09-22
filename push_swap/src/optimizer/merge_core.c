/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

/*
 * Calculates the absorption result for RR and RRA operations.
 *
 * This function implements the absorption logic for cases where
 * RR (rotate both) and RRA (reverse rotate A) operations can be
 * combined into a single operation:
 * - If first operation is RR: result is RB (rotate B only)
 * - If first operation is RRA: result is RRB (reverse rotate B only)
 *
 * @param a: First operation in the pair (RR or RRA)
 * @return: Absorbed operation that replaces the pair
 */
t_operation	get_absorption_rr_rra(t_operation a)
{
	if (a == RR)
		return (RB);
	return (RRB);
}

/*
 * Calculates the absorption result for RR and RRB operations.
 *
 * This function implements the absorption logic for cases where
 * RR (rotate both) and RRB (reverse rotate B) operations can be
 * combined into a single operation:
 * - If first operation is RR: result is RA (rotate A only)
 * - If first operation is RRB: result is RRA (reverse rotate A only)
 *
 * @param a: First operation in the pair (RR or RRB)
 * @return: Absorbed operation that replaces the pair
 */
t_operation	get_absorption_rr_rrb(t_operation a)
{
	if (a == RR)
		return (RA);
	return (RRA);
}

/*
 * Calculates the absorption result for RRR and RA operations.
 *
 * This function implements the absorption logic for cases where
 * RRR (reverse rotate both) and RA (rotate A) operations can be
 * combined into a single operation:
 * - If first operation is RRR: result is RRB (reverse rotate B only)
 * - If first operation is RA: result is RB (rotate B only)
 *
 * @param a: First operation in the pair (RRR or RA)
 * @return: Absorbed operation that replaces the pair
 */
t_operation	get_absorption_rrr_ra(t_operation a)
{
	if (a == RRR)
		return (RRB);
	return (RB);
}

/*
 * Calculates the absorption result for RRR and RB operations.
 *
 * This function implements the absorption logic for cases where
 * RRR (reverse rotate both) and RB (rotate B) operations can be
 * combined into a single operation:
 * - If first operation is RRR: result is RRA (reverse rotate A only)
 * - If first operation is RB: result is RA (rotate A only)
 *
 * @param a: First operation in the pair (RRR or RB)
 * @return: Absorbed operation that replaces the pair
 */
t_operation	get_absorption_rrr_rb(t_operation a)
{
	if (a == RRR)
		return (RRA);
	return (RA);
}
