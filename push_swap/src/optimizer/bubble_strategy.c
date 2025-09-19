/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_strategy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:50:28 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 23:11:22 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

static void	process_all_operations(t_bubble_context *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->n - 1)
	{
		ctx->i = i;
		process_operation_at_index(ctx);
		i++;
	}
}

t_list	*bubble_next_stack(t_list *src, bool *changed)
{
	int					n;
	t_list				*out;
	t_bubble_context	ctx;

	n = ft_lstsize(src);
	if (n < 3)
	{
		*changed = false;
		return (src);
	}
	out = ft_lstmap(src, copy_operation, free);
	if (out == NULL)
		return (NULL);
	*changed = false;
	ctx.out = out;
	ctx.n = n;
	ctx.max_gap = 4;
	ctx.changed = changed;
	ctx.is_a = false;
	process_all_operations(&ctx);
	return (out);
}
