/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:12:48 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 22:12:51 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	search_and_bubble_b(t_bubble_context *ctx)
{
	t_operation	a;
	t_operation	want;
	int			j;
	t_operation	op_j;

	a = get_operation_at_index(ctx->out, ctx->i);
	want = get_target_operation_for_b(a);
	j = ctx->i + 1;
	while (j < ctx->n && j - ctx->i - 1 <= ctx->max_gap)
	{
		op_j = get_operation_at_index(ctx->out, j);
		if (op_j == want)
		{
			if (bubble_operation(ctx->out, ctx->i, j, false))
				*ctx->changed = true;
			return (true);
		}
		if (is_barrier(op_j) || touches_b(op_j))
			break ;
		j++;
	}
	return (false);
}

bool	search_and_bubble_a(t_bubble_context *ctx)
{
	t_operation	a;
	t_operation	want;
	int			j;
	t_operation	op_j;

	a = get_operation_at_index(ctx->out, ctx->i);
	want = get_target_operation_for_a(a);
	j = ctx->i + 1;
	while (j < ctx->n && j - ctx->i - 1 <= ctx->max_gap)
	{
		op_j = get_operation_at_index(ctx->out, j);
		if (op_j == want)
		{
			if (bubble_operation(ctx->out, ctx->i, j, true))
				*ctx->changed = true;
			return (true);
		}
		if (is_barrier(op_j) || touches_a(op_j))
			break ;
		j++;
	}
	return (false);
}

void	process_operation_at_index(t_bubble_context *ctx)
{
	t_operation	a;

	a = get_operation_at_index(ctx->out, ctx->i);
	if (a == RA || a == RRA)
	{
		ctx->is_a = true;
		search_and_bubble_a(ctx);
	}
	else if (a == RB || a == RRB)
	{
		ctx->is_a = false;
		search_and_bubble_b(ctx);
	}
}
