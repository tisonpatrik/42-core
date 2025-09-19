/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_strategy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:53 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 23:13:10 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

static t_operation	get_inverse_a_operation(t_operation op)
{
	if (op == RA)
		return (RRA);
	return (RA);
}

static t_operation	get_inverse_b_operation(t_operation op)
{
	if (op == RB)
		return (RRB);
	return (RB);
}

void	copy_operations_to_list(t_list **dst, t_list *src_start,
		t_list *src_end)
{
	t_list	*current;

	current = src_start;
	while (current != src_end)
	{
		add_operation_to_list(dst, *(t_operation *)current->content);
		current = current->next;
	}
}

bool	search_for_inverse_a(t_operation op, t_list *current, t_list **dst,
		bool *has_changed)
{
	t_operation	inv;
	t_list		*search;

	inv = get_inverse_a_operation(op);
	search = current->next;
	while (search != NULL)
	{
		if (is_barrier(*(t_operation *)search->content)
			|| touches_a(*(t_operation *)search->content))
			break ;
		if (*(t_operation *)search->content == inv)
		{
			*has_changed = true;
			copy_operations_to_list(dst, current->next, search);
			return (true);
		}
		search = search->next;
	}
	return (false);
}

bool	search_for_inverse_b(t_operation op, t_list *current, t_list **dst,
		bool *has_changed)
{
	t_operation	inv;
	t_list		*search;

	inv = get_inverse_b_operation(op);
	search = current->next;
	while (search != NULL)
	{
		if (is_barrier(*(t_operation *)search->content)
			|| touches_b(*(t_operation *)search->content))
			break ;
		if (*(t_operation *)search->content == inv)
		{
			*has_changed = true;
			copy_operations_to_list(dst, current->next, search);
			return (true);
		}
		search = search->next;
	}
	return (false);
}
