/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:51:56 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
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

void	reverse_rotate_a(t_sorting_state *state)
{
	bool	success;

	success = reverse_rotate(&state->a);
	if (success)
		save_operation(state, RRA);
}

void	reverse_rotate_b(t_sorting_state *state)
{
	bool	success;

	success = reverse_rotate(&state->b);
	if (success)
		save_operation(state, RRB);
}

void	reverse_rotate_ab(t_sorting_state *state)
{
	bool	success_a;
	bool	success_b;

	success_a = reverse_rotate(&state->a);
	success_b = reverse_rotate(&state->b);
	if (success_a && success_b)
		save_operation(state, RRR);
}
