/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:58:29 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:30 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/stack.h"
#include "checker_bonus.h"
#include <stdbool.h>
#include <unistd.h>

static bool	rotate(t_stack **stack)
{
	t_node	*top_node;
	t_node	*tail_node;

	if (!stack || !*stack)
		return (false);
	if (get_size(*stack) <= 1)
		return (false);
	top_node = get_head(*stack);
	tail_node = get_tail(*stack);
	(*stack)->head = get_next(top_node);
	(*stack)->head->prev = NULL;
	top_node->next = NULL;
	top_node->prev = tail_node;
	tail_node->next = top_node;
	(*stack)->tail = top_node;
	return (true);
}

bool	apply_rotate_operation(t_checker_state *state, t_operation op)
{
	if (op == RA)
	{
		if (get_size(state->a) < 2)
			return (false);
		return (rotate(&state->a));
	}
	else if (op == RB)
	{
		if (get_size(state->b) < 2)
			return (false);
		return (rotate(&state->b));
	}
	else if (op == RR)
	{
		if (get_size(state->a) < 2 || get_size(state->b) < 2)
			return (false);
		if (!rotate(&state->a) || !rotate(&state->b))
			return (false);
		return (true);
	}
	return (false);
}
