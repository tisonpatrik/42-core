/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:51:56 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 19:50:46 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/stack.h"
#include "checker_bonus.h"
#include <stdbool.h>
#include <unistd.h>

static bool	reverse_rotate(t_stack **stack)
{
	t_node	*bottom_node;
	t_node	*head_node;
	t_node	*prev_tail;

	if (!stack || !*stack)
		return (false);
	if (get_size(*stack) <= 1)
		return (false);
	bottom_node = get_tail(*stack);
	head_node = get_head(*stack);
	prev_tail = get_prev(bottom_node);
	(*stack)->tail = prev_tail;
	prev_tail->next = NULL;
	bottom_node->prev = NULL;
	bottom_node->next = head_node;
	head_node->prev = bottom_node;
	(*stack)->head = bottom_node;
	return (true);
}

bool	apply_reverse_rotate_operation(t_checker_state *state, t_operation op)
{
	if (op == RRA)
	{
		if (get_size(state->a) < 2)
			return (false);
		return (reverse_rotate(&state->a));
	}
	else if (op == RRB)
	{
		if (get_size(state->b) < 2)
			return (false);
		return (reverse_rotate(&state->b));
	}
	else if (op == RRR)
	{
		if (get_size(state->a) < 2 || get_size(state->b) < 2)
			return (false);
		if (!reverse_rotate(&state->a) || !reverse_rotate(&state->b))
			return (false);
		return (true);
	}
	return (false);
}
