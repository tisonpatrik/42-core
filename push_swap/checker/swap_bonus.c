/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:57:23 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:30 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/stack.h"
#include "checker_bonus.h"
#include <stdbool.h>
#include <unistd.h>

static bool	swap(t_stack **stack)
{
	int		temp_content;
	t_node	*first_node;
	t_node	*second_node;

	if (!stack || !*stack)
		return (false);
	if (get_size(*stack) < 2)
		return (false);
	first_node = get_head(*stack);
	second_node = get_next(first_node);
	temp_content = get_content(first_node);
	first_node->content = get_content(second_node);
	second_node->content = temp_content;
	return (true);
}

bool	apply_swap_operation(t_checker_state *state, t_operation op)
{
	if (op == SA)
	{
		if (get_size(state->a) < 2)
			return (false);
		return (swap(&state->a));
	}
	else if (op == SB)
	{
		if (get_size(state->b) < 2)
			return (false);
		return (swap(&state->b));
	}
	else if (op == SS)
	{
		if (get_size(state->a) < 2 || get_size(state->b) < 2)
			return (false);
		if (!swap(&state->a) || !swap(&state->b))
			return (false);
		return (true);
	}
	return (false);
}
