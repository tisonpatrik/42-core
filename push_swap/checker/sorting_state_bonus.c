/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:58:57 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 18:35:10 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/stack.h"
#include "checker_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static void	cleanup_failed_state(t_checker_state *state, t_stack *a, t_stack *b)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	if (state)
		free(state);
}

static t_checker_state	*create_checker_state(int *numbers, int len)
{
	t_checker_state	*state;
	t_stack			*a;
	t_stack			*b;

	if (!numbers || len <= 0)
		return (NULL);
	state = malloc(sizeof(t_checker_state));
	if (!state)
		return (NULL);
	a = create_stack();
	b = create_stack();
	if (!a || !b)
	{
		cleanup_failed_state(state, a, b);
		return (NULL);
	}
	fill_stack(a, numbers, len);
	state->a = a;
	state->b = b;
	state->operations = NULL;
	state->len_of_inputs = len;
	return (state);
}

void	free_checker_state(t_checker_state *state)
{
	if (!state)
		return ;
	if (state->a)
		free_stack(state->a);
	if (state->b)
		free_stack(state->b);
	if (state->operations)
	{
		ft_lstclear(&state->operations, free);
	}
	free(state);
}

t_checker_state	*create_state_for_checker(int *numbers, int n,
		t_list *operations)
{
	t_checker_state	*state;

	state = create_checker_state(numbers, n);
	if (!state)
		return (NULL);
	state->operations = operations;
	return (state);
}
