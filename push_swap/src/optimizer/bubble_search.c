/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:12:48 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 11:14:21 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

/*
 * Gets the target operation for stack A operations during bubble search.
 *
 * This function determines what operation should be paired with
 * a stack A operation for optimal bubble sorting:
 * - RA → RB (rotate A should be paired with rotate B)
 * - RRA → RRB (reverse rotate A should be paired with reverse rotate B)
 *
 * @param a: Stack A operation to find target for
 * @return: Target operation that should be paired with the input
 */
t_operation	get_target_operation_for_a(t_operation a)
{
	if (a == RA)
		return (RB);
	return (RRB);
}

/*
 * Gets the target operation for stack B operations during bubble search.
 *
 * This function determines what operation should be paired with
 * a stack B operation for optimal bubble sorting:
 * - RB → RA (rotate B should be paired with rotate A)
 * - RRB → RRA (reverse rotate B should be paired with reverse rotate A)
 *
 * @param a: Stack B operation to find target for
 * @return: Target operation that should be paired with the input
 */
t_operation	get_target_operation_for_b(t_operation a)
{
	if (a == RB)
		return (RA);
	return (RRA);
}

/*
 * Searches for and bubbles stack B operations to pair with stack A operations.
 *
 * This function implements the bubble search strategy for stack B:
 * 1. Determines the target operation that should be paired
 * 2. Searches forward within the maximum gap limit
 * 3. Stops at barrier operations or operations that touch stack B
 * 4. If target found: attempts to bubble it to the correct position
 *
 * @param ctx: Bubble context containing search parameters and state
 * @return: True if target was found and bubbled, false otherwise
 */
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

/*
 * Searches for and bubbles stack A operations to pair with stack B operations.
 *
 * This function implements the bubble search strategy for stack A:
 * 1. Determines the target operation that should be paired
 * 2. Searches forward within the maximum gap limit
 * 3. Stops at barrier operations or operations that touch stack A
 * 4. If target found: attempts to bubble it to the correct position
 *
 * @param ctx: Bubble context containing search parameters and state
 * @return: True if target was found and bubbled, false otherwise
 */
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

/*
 * Processes an operation at a specific index for bubble optimization.
 *
 * This function determines the type of operation and applies
 * the appropriate bubble search strategy:
 * 1. For stack A operations (RA, RRA): searches for stack A targets
 * 2. For stack B operations (RB, RRB): searches for stack B targets
 *
 * The function sets the appropriate context flags and calls
 * the corresponding search and bubble function.
 *
 * @param ctx: Bubble context containing the operation index and state
 */
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
