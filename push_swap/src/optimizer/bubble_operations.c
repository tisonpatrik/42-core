/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:50:41 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 21:31:54 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

void	set_operation_at_index(t_list *list, int index, t_operation op)
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
	if (current != NULL)
		*(t_operation *)current->content = op;
}

static bool	can_bubble_operation(t_list *out, int i, int j, bool is_a)
{
	t_operation	op_k;
	int			k;

	k = i + 1;
	while (k < j)
	{
		op_k = get_operation_at_index(out, k);
		if (is_barrier(op_k))
			return (false);
		if (is_a && (touches_a(op_k) || (!touches_b(op_k) && !is_pure_b(op_k))))
			return (false);
		if (!is_a && (touches_b(op_k) || (!touches_a(op_k)
					&& !is_pure_a(op_k))))
			return (false);
		k++;
	}
	return (true);
}

bool	bubble_operation(t_list *out, int i, int j, bool is_a)
{
	t_operation	temp;
	int			k;

	if (!can_bubble_operation(out, i, j, is_a))
		return (false);
	k = j;
	while (k > i + 1)
	{
		temp = get_operation_at_index(out, k);
		set_operation_at_index(out, k, get_operation_at_index(out, k - 1));
		set_operation_at_index(out, k - 1, temp);
		k--;
	}
	return (true);
}

void	process_all_operations(t_bubble_context *ctx)
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

t_list	*bubble_across_other_stack(t_list *src, int max_gap, bool *changed)
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
	ctx.max_gap = max_gap;
	ctx.changed = changed;
	ctx.is_a = false;
	process_all_operations(&ctx);
	return (out);
}
