/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:58:29 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 23:09:55 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
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

void	rotate_a(t_sorting_state *state)
{
	bool	success;

	success = rotate(&state->a);
	if (success)
		save_operation(state, RA);
}

void	rotate_b(t_sorting_state *state)
{
	bool	success;

	success = rotate(&state->b);
	if (success)
		save_operation(state, RB);
}

void	rotate_ab(t_sorting_state *state)
{
	bool	success_a;
	bool	success_b;

	success_a = rotate(&state->a);
	success_b = rotate(&state->b);
	if (success_a && success_b)
		save_operation(state, RR);
}
