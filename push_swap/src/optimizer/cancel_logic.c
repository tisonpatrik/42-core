/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:58 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 21:06:34 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

t_list	*cancel_across_other_stack_a(t_list *src, bool *changed)
{
	t_optimizer_arena	*arena;
	t_list				*dst;
	t_list				*current;
	bool				has_changed;
	t_operation			op;
	t_cancel_context	ctx;

	if (!src || ft_lstsize(src) < 3)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	arena = create_optimizer_arena(ft_lstsize(src));
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	dst = NULL;
	has_changed = false;
	current = src;
	while (current != NULL)
	{
		op = *(t_operation *)current->content;
		ctx.op = op;
		ctx.current = current;
		ctx.dst = &dst;
		ctx.has_changed = &has_changed;
		ctx.current_ptr = &current;
		process_operation_a(&ctx);
		current = current->next;
	}
	if (changed)
		*changed = has_changed;
	destroy_optimizer_arena(arena);
	return (dst);
}

void	process_operation_b(t_cancel_context *ctx)
{
	if (ctx->op == RB || ctx->op == RRB)
	{
		if (search_for_inverse_b(ctx->op, ctx->current, ctx->dst, ctx->has_changed))
		{
			*ctx->current_ptr = ctx->current;
			return ;
		}
	}
	add_operation_to_list(ctx->dst, ctx->op);
}

t_list	*cancel_across_other_stack_b(t_list *src, bool *changed)
{
	t_optimizer_arena	*arena;
	t_list				*dst;
	t_list				*current;
	bool				has_changed;
	t_operation			op;
	t_cancel_context	ctx;

	if (!src || ft_lstsize(src) < 3)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	arena = create_optimizer_arena(ft_lstsize(src));
	if (!arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	dst = NULL;
	has_changed = false;
	current = src;
	while (current != NULL)
	{
		op = *(t_operation *)current->content;
		ctx.op = op;
		ctx.current = current;
		ctx.dst = &dst;
		ctx.has_changed = &has_changed;
		ctx.current_ptr = &current;
		process_operation_b(&ctx);
		current = current->next;
	}
	if (changed)
		*changed = has_changed;
	destroy_optimizer_arena(arena);
	return (dst);
}
