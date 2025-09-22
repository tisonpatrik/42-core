/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:48:29 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 11:31:46 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

void	*copy_operation(void *content)
{
	t_operation	*op;

	op = malloc(sizeof(t_operation));
	if (op)
		*op = *(t_operation *)content;
	return (op);
}

void	add_operation_to_list(t_list **dst, t_operation op)
{
	t_operation	*op_ptr;

	op_ptr = malloc(sizeof(t_operation));
	if (op_ptr)
	{
		*op_ptr = op;
		ft_lstadd_back(dst, ft_lstnew(op_ptr));
	}
}

t_operation	get_operation_at_index(t_list *list, int index)
{
	t_list	*current;
	int		i;

	current = list;
	i = 0;
	while (current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	if (current == NULL)
		return (SA);
	return (*(t_operation *)current->content);
}

/*
 * Replaces the sequence if changes were made during optimization.
 *
 * This function handles the replacement of operation sequences
 * after optimization:
 * 1. If changes were made: replaces the old sequence with the new one
 * 2. If no changes: frees the new sequence to avoid memory leaks
 * 3. Updates the overall change flag if changes occurred
 *
 * @param seq: Pointer to the original sequence
 * @param new_seq: New optimized sequence
 * @param changed: Flag indicating if changes were made
 * @param overall_changed: Pointer to overall change flag
 */
void	replace_sequence_if_changed(t_list **seq, t_list *new_seq, bool changed,
		bool *overall_changed)
{
	if (changed)
	{
		ft_lstclear(seq, free);
		*seq = new_seq;
		*overall_changed = true;
	}
	else
	{
		ft_lstclear(&new_seq, free);
	}
}

/*
 * Processes operations for stack A during cross-stack cancellation.
 *
 * This function handles the processing of stack A operations during
 * the cross-stack cancellation phase:
 * 1. Checks if the operation is RA or RRA
 * 2. Searches for inverse operations in stack B
 * 3. If inverse found: cancels both operations
 * 4. If no inverse found: adds the operation to the result
 *
 * @param ctx: Cancel context containing operation and processing state
 */
void	process_operation_a(t_cancel_context *ctx)
{
	if (ctx->op == RA || ctx->op == RRA)
	{
		if (search_for_inverse_a(ctx->op, ctx->current, ctx->dst,
				ctx->has_changed))
		{
			*ctx->current_ptr = ctx->current;
			return ;
		}
	}
	add_operation_to_list(ctx->dst, ctx->op);
}
