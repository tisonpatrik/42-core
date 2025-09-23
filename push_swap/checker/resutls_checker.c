/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resutls_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:07:40 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 18:56:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/stack.h"
#include <stdbool.h>
#include <stdlib.h>
#include "checker_bonus.h"

void validate_inputs(t_checker_state *state)
{
    if (state->a->size == 0)
    {
        exit(1);
    }
}



static bool	apply_operation(t_checker_state *state, t_operation op)
{
	if (op == SA)
	{
		if (get_size(state->a) < 2)
			return (false);
		swap(&state->a);
	}
	else if (op == SB)
	{
		if (get_size(state->b) < 2)
			return (false);
		swap(&state->b);
	}
	else if (op == SS)
	{
		if (get_size(state->a) < 2 || get_size(state->b) < 2)
			return (false);
		swap(&state->a);
		swap(&state->b);
	}
	else if (op == PA)
	{
		if (get_size(state->b) == 0)
			return (false);
		push(&state->b, &state->a);
	}
	else if (op == PB)
	{
		if (get_size(state->a) == 0)
			return (false);
		push(&state->a, &state->b);
	}
	else if (op == RA)
	{
		if (get_size(state->a) < 2)
			return (false);
		rotate(&state->a);
	}
	else if (op == RB)
	{
		if (get_size(state->b) < 2)
			return (false);
		rotate(&state->b);
	}
	else if (op == RR)
	{
		if (get_size(state->a) < 2 || get_size(state->b) < 2)
			return (false);
		rotate(&state->a);
		rotate(&state->b);
	}
	else if (op == RRA)
	{
		if (get_size(state->a) < 2)
			return (false);
		reverse_rotate(&state->a);
	}
	else if (op == RRB)
	{
		if (get_size(state->b) < 2)
			return (false);
		reverse_rotate(&state->b);
	}
	else if (op == RRR)
	{
		if (get_size(state->a) < 2 || get_size(state->b) < 2)
			return (false);
		reverse_rotate(&state->a);
		reverse_rotate(&state->b);
	}
	return (true);
}

void	check_result(t_checker_state *state)
{
	t_list	*current;
	t_operation	*op;

	if (!state)
	{
		ft_printf("KO\n");
		return ;
	}
	validate_inputs(state);
	if (!state->operations)
	{
		if (is_sorted(state->a) && state->b->size == 0)
		{
			ft_printf("OK\n");
		}
		else
		{
			ft_printf("KO\n");
		}
		return ;
	}
	current = state->operations;
	while (current)
	{
		op = (t_operation *)current->content;
		if (!apply_operation(state, *op))
		{
			ft_printf("KO\n");
			return ;
		}
		current = current->next;
	}

	if (is_sorted(state->a) && state->b->size == 0)
	{
		ft_printf("OK\n");
	}
	else
	{
		ft_printf("KO\n");
	}
}