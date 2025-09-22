/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:58 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 11:43:28 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

static t_list	*process_operations_loop(t_list *src, bool *has_changed,
		void (*process_func)(t_cancel_context *))
{
	t_list				*dst;
	t_list				*current;
	t_operation			op;
	t_cancel_context	ctx;

	dst = NULL;
	current = src;
	while (current != NULL)
	{
		op = *(t_operation *)current->content;
		ctx.op = op;
		ctx.current = current;
		ctx.dst = &dst;
		ctx.has_changed = has_changed;
		ctx.current_ptr = &current;
		process_func(&ctx);
		current = current->next;
	}
	return (dst);
}

static t_list	*process_cancel_operations(t_list *src, bool *changed,
		void (*process_func)(t_cancel_context *))
{
	t_list	*dst;
	bool	has_changed;

	has_changed = false;
	dst = process_operations_loop(src, &has_changed, process_func);
	if (changed)
		*changed = has_changed;
	return (dst);
}

/*
 * Processes operations for stack B during cross-stack cancellation.
 *
 * This function handles the processing of stack B operations during
 * the cross-stack cancellation phase:
 * 1. Checks if the operation is RB or RRB
 * 2. Searches for inverse operations in stack A
 * 3. If inverse found: cancels both operations
 * 4. If no inverse found: adds the operation to the result
 *
 * @param ctx: Cancel context containing operation and processing state
 */
static void	process_operation_b(t_cancel_context *ctx)
{
	if (ctx->op == RB || ctx->op == RRB)
	{
		if (search_for_inverse_b(ctx->op, ctx->current, ctx->dst,
				ctx->has_changed))
		{
			*ctx->current_ptr = ctx->current;
			return ;
		}
	}
	add_operation_to_list(ctx->dst, ctx->op);
}

/*
 * Cancels operations across stack B by finding inverse operations in stack A.
 *
 * This function implements cross-stack cancellation for stack B:
 * 1. Validates input sequence (requires at least 3 operations)
 * 2. Processes stack B operations to find inverse operations in stack A
 * 3. Cancels operations that have inverse counterparts
 * 4. Returns optimized sequence with cancellations applied
 *
 * @param src: Source operation sequence to optimize
 * @param changed: Pointer to flag indicating if changes were made
 * @return: Optimized operation sequence with cross-stack cancellations
 */
t_list	*cancel_across_other_stack_b(t_list *src, bool *changed)
{
	if (!src || ft_lstsize(src) < 3)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	return (process_cancel_operations(src, changed, process_operation_b));
}

/*
 * Cancels operations across stack A by finding inverse operations in stack B.
 *
 * This function implements cross-stack cancellation for stack A:
 * 1. Validates input sequence (requires at least 3 operations)
 * 2. Processes stack A operations to find inverse operations in stack B
 * 3. Cancels operations that have inverse counterparts
 * 4. Returns optimized sequence with cancellations applied
 *
 * @param src: Source operation sequence to optimize
 * @param changed: Pointer to flag indicating if changes were made
 * @return: Optimized operation sequence with cross-stack cancellations
 */
t_list	*cancel_across_other_stack_a(t_list *src, bool *changed)
{
	if (!src || ft_lstsize(src) < 3)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	return (process_cancel_operations(src, changed, process_operation_a));
}
