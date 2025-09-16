/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:58:57 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 21:58:15 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include <stdlib.h>
#include <unistd.h>

t_sorting_state	*create_sorting_state(int *numbers, int n)
{
	t_sorting_state	*state;
	t_stack			*a;
	t_stack			*b;

	if (!numbers || n <= 0)
		return (NULL);
	state = malloc(sizeof(t_sorting_state));
	if (!state)
		return (NULL);
	a = create_stack();
	b = create_stack();
	if (!a || !b)
	{
		if (a)
			clear_stack(a);
		if (b)
			clear_stack(b);
		free(state);
		return (NULL);
	}
	fill_stack(a, numbers, n);
	state->a = a;
	state->b = b;
	state->operations = NULL;
	return (state);
}

void	free_sorting_state(t_sorting_state *state)
{
	if (!state)
		return ;
	if (state->a)
	{
		clear_stack(state->a);
		free(state->a);
	}
	if (state->b)
	{
		clear_stack(state->b);
		free(state->b);
	}
	if (state->operations)
	{
		print_operations(state);
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

void print_operation(t_operation op)
{
		if (op == SA)
			ft_printf("sa\n");
		else if (op == SB)
			ft_printf("sb\n");
		else if (op == SS)
			ft_printf("ss\n");
		else if (op == PA)
			ft_printf("pa\n");
		else if (op == PB)
			ft_printf("pb\n");
		else if (op == RA)
			ft_printf("ra\n");
		else if (op == RB)
			ft_printf("rb\n");
		else if (op == RR)
			ft_printf("rr\n");
		else if (op == RRA)
			ft_printf("rra\n");
		else if (op == RRB)
			ft_printf("rrb\n");
		else if (op == RRR)
			ft_printf("rrr\n");
}

void	print_operations(t_sorting_state *state)
{
	t_list		*current;
	t_operation	op;

	current = state->operations;
	while (current != NULL)
	{
		op = *(t_operation *)current->content;
		print_operation(op);
		current = current->next;
	}
}
