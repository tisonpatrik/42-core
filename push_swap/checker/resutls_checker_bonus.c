/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resutls_checker_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:07:40 by ptison            #+#    #+#             */
/*   Updated: 2025/09/25 15:42:44 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/stack.h"
#include "checker_bonus.h"
#include <stdbool.h>

static bool	apply_operation(t_checker_state *state, t_operation op)
{
	if (apply_swap_operation(state, op))
		return (true);
	if (apply_push_operation(state, op))
		return (true);
	if (apply_rotate_operation(state, op))
		return (true);
	if (apply_reverse_rotate_operation(state, op))
		return (true);
	return (false);
}

static bool	execute_operations(t_checker_state *state)
{
	t_list		*current;
	t_operation	*op;

	current = state->operations;
	while (current)
	{
		op = (t_operation *)current->content;
		if (!apply_operation(state, *op))
			return (false);
		current = current->next;
	}
	return (true);
}

void	check_result(t_checker_state *state)
{
	if (!state)
	{
		ft_printf("KO\n");
		return ;
	}
	if (!state->operations)
	{
		if (is_sorted(state->a) && state->b->size == 0)
			ft_printf("OK\n");
		else
			ft_printf("KO\n");
		return ;
	}
	if (!execute_operations(state))
	{
		ft_printf("KO\n");
		return ;
	}
	if (is_sorted(state->a) && state->b->size == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}
