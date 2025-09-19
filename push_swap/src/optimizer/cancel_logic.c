/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:58 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 23:12:35 by patrik           ###   ########.fr       */
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
	t_list				*dst;
	bool				has_changed;

	has_changed = false;
	dst = process_operations_loop(src, &has_changed, process_func);
	if (changed)
		*changed = has_changed;
	return (dst);
}

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
