/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:21:27 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:29 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include <stdbool.h>
#include <unistd.h>

static bool	push(t_stack **source, t_stack **target)
{
	t_node	*popped_node;

	if (!source || !*source)
		return (false);
	if (!target || !*target)
		return (false);
	if (get_size(*source) == 0)
		return (false);
	popped_node = pop(source);
	if (!popped_node)
		return (false);
	push_to_stack(*target, popped_node);
	return (true);
}

void	push_a(t_sorting_state *state)
{
	bool	success;

	success = push(&state->b, &state->a);
	if (success)
		save_operation(state, PA);
}

void	push_b(t_sorting_state *state)
{
	bool	success;

	success = push(&state->a, &state->b);
	if (success)
		save_operation(state, PB);
}
