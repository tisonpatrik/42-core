/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:21:27 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 19:50:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/stack.h"
#include "checker_bonus.h"
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

bool	apply_push_operation(t_checker_state *state, t_operation op)
{
	if (op == PA)
	{
		if (get_size(state->b) == 0)
			return (false);
		return (push(&state->b, &state->a));
	}
	else if (op == PB)
	{
		if (get_size(state->a) == 0)
			return (false);
		return (push(&state->a, &state->b));
	}
	return (false);
}
