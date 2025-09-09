/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:58:29 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 18:58:41 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include <stdbool.h>
#include <unistd.h>

bool	rotate(t_stack **stack)
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
