/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_strategy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:50:28 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:29 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

/*
 * Processes all operations in the sequence using bubble sort optimization.
 *
 * This function implements the bubble sort algorithm for operation sequences:
 * 1. Iterates through all operations in the sequence
 * 2. For each operation, attempts to bubble it to a better position
 * 3. Uses the bubble context to track optimization progress
 *
 * @param ctx: Bubble context containing sequence and optimization parameters
 */
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

/*
 * Applies bubble sort optimization to reorder operations for better efficiency.
 *
 * This function implements the bubble sort strategy for operation sequences:
 * 1. Creates a copy of the input sequence
 * 2. Applies bubble sort to reorder operations optimally
 * 3. Returns the optimized sequence if changes were made
 *
 * @param src: Source operation sequence to optimize
 * @param changed: Pointer to flag indicating if changes were made
 * @return: Optimized operation sequence, or original if no changes
 */
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
