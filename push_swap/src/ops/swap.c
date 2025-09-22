/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:57:23 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
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

void	swap_a(t_sorting_state *state)
{
	bool	success;

	success = swap(&state->a);
	if (success)
		save_operation(state, SA);
}

void	swap_b(t_sorting_state *state)
{
	bool	success;

	success = swap(&state->b);
	if (success)
		save_operation(state, SB);
}

void	swap_ab(t_sorting_state *state)
{
	bool	success_a;
	bool	success_b;

	success_a = swap(&state->a);
	success_b = swap(&state->b);
	if (success_a && success_b)
		save_operation(state, SS);
}
