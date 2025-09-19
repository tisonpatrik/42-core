/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:30 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 21:28:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

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

bool	try_merge_absorption_cases(t_merge_context *ctx)
{
	if ((ctx->a == RR && ctx->b == RRA) || (ctx->a == RRA && ctx->b == RR))
	{
		add_operation_to_list(ctx->dst, get_absorption_result_rr_rra(ctx->a));
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	if ((ctx->a == RR && ctx->b == RRB) || (ctx->a == RRB && ctx->b == RR))
	{
		add_operation_to_list(ctx->dst, get_absorption_result_rr_rrb(ctx->a));
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	if ((ctx->a == RRR && ctx->b == RA) || (ctx->a == RA && ctx->b == RRR))
	{
		add_operation_to_list(ctx->dst, get_absorption_result_rrr_ra(ctx->a));
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	if ((ctx->a == RRR && ctx->b == RB) || (ctx->a == RB && ctx->b == RRR))
	{
		add_operation_to_list(ctx->dst, get_absorption_result_rrr_rb(ctx->a));
		*ctx->current = (*ctx->current)->next->next;
		return (true);
	}
	return (false);
}
