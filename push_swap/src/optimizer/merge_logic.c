/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:30 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:29 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

/*
 * Attempts to merge rotate operation pairs into combined operations.
 *
 * This function implements the merge logic for rotate operations:
 * 1. RA + RB or RB + RA → RR (rotate both)
 * 2. RRA + RRB or RRB + RRA → RRR (reverse rotate both)
 *
 * When two single-stack rotations can be combined into a dual-stack
 * rotation, this reduces two operations to one, improving efficiency.
 *
 * @param ctx: Merge context containing the two operations to merge
 * @return: True if merge was successful, false otherwise
 */
bool	try_merge_rotate_pairs(t_merge_context *ctx)
{
	if ((ctx->a == RA && ctx->b == RB) || (ctx->a == RB && ctx->b == RA))
	{
		add_operation_to_list(ctx->dst, RR);
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	if ((ctx->a == RRA && ctx->b == RRB) || (ctx->a == RRB && ctx->b == RRA))
	{
		add_operation_to_list(ctx->dst, RRR);
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	return (false);
}

/*
 * Attempts to merge swap operation pairs into combined operations.
 *
 * This function implements the merge logic for swap operations:
 * - SA + SB or SB + SA → SS (swap both)
 *
 * When two single-stack swaps can be combined into a dual-stack
 * swap, this reduces two operations to one, improving efficiency.
 *
 * @param ctx: Merge context containing the two operations to merge
 * @return: True if merge was successful, false otherwise
 */
bool	try_merge_swap_pairs(t_merge_context *ctx)
{
	if ((ctx->a == SA && ctx->b == SB) || (ctx->a == SB && ctx->b == SA))
	{
		add_operation_to_list(ctx->dst, SS);
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	return (false);
}

/*
 * Attempts to merge operations using absorption cases.
 *
 * This function implements absorption logic for specific operation pairs:
 * 1. RR + RRA or RRA + RR → Single operation (using get_absorption_rr_rra)
 * 2. RR + RRB or RRB + RR → Single operation (using get_absorption_rr_rrb)
 * 3. RRR + RA or RA + RRR → Single operation (using get_absorption_rrr_ra)
 * 4. RRR + RB or RB + RRR → Single operation (using get_absorption_rrr_rb)
 *
 * Absorption occurs when a dual-stack operation and a single-stack
 * operation can be combined, eliminating redundant rotations.
 *
 * @param ctx: Merge context containing the two operations to merge
 * @return: True if absorption was successful, false otherwise
 */
bool	try_merge_absorption_cases(t_merge_context *ctx)
{
	if ((ctx->a == RR && ctx->b == RRA) || (ctx->a == RRA && ctx->b == RR))
	{
		add_operation_to_list(ctx->dst, get_absorption_rr_rra(ctx->a));
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	if ((ctx->a == RR && ctx->b == RRB) || (ctx->a == RRB && ctx->b == RR))
	{
		add_operation_to_list(ctx->dst, get_absorption_rr_rrb(ctx->a));
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	if ((ctx->a == RRR && ctx->b == RA) || (ctx->a == RA && ctx->b == RRR))
	{
		add_operation_to_list(ctx->dst, get_absorption_rrr_ra(ctx->a));
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	if ((ctx->a == RRR && ctx->b == RB) || (ctx->a == RB && ctx->b == RRR))
	{
		add_operation_to_list(ctx->dst, get_absorption_rrr_rb(ctx->a));
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	return (false);
}
