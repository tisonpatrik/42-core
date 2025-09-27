/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:58:57 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:29 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include <stdlib.h>
#include <unistd.h>

static void	cleanup_failed_state(t_sorting_state *state, t_stack *a, t_stack *b)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	if (state)
		free(state);
}

t_sorting_state	*create_sorting_state(int *numbers, int len)
{
	t_sorting_state	*state;
	t_stack			*a;
	t_stack			*b;

	if (!numbers || len <= 0)
		return (NULL);
	state = malloc(sizeof(t_sorting_state));
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

void	free_sorting_state(t_sorting_state *state)
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

void	save_operation(t_sorting_state *state, t_operation operation)
{
	t_list	*new_node;
	int		*op_ptr;

	if (!state)
		return ;
	op_ptr = malloc(sizeof(int));
	if (!op_ptr)
		return ;
	*op_ptr = operation;
	new_node = ft_lstnew(op_ptr);
	if (!new_node)
	{
		free(op_ptr);
		return ;
	}
	ft_lstadd_back(&state->operations, new_node);
}
