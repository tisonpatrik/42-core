/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:58:57 by ptison            #+#    #+#             */
/*   Updated: 2025/09/15 21:52:22 by patrik           ###   ########.fr       */
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

void	print_operations(t_sorting_state *state)
{
	t_list	*current;
	char	*operation_strings[] = {
		"sa\n", "sb\n", "ss\n", "pa\n", "pb\n", 
		"ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"
	};

	if (!state || !state->operations)
		return ;
	
	current = state->operations;
	while (current != NULL)
	{
		t_operation op = *(t_operation*)current->content;
		if (op >= SA && op <= RRR)
		{
			write(1, operation_strings[op], ft_strlen(operation_strings[op]));
		}
		current = current->next;
	}
}


void print_state_values(t_sorting_state *state)
{
	// Print stack A with "A: " prefix and square brackets
	write(1, "A: [", 4);
	print_stack_values(state->a);
	write(1, "]\n", 2);
	
	// Print stack B with "B: " prefix and square brackets
	write(1, "B: [", 4);
	print_stack_values(state->b);
	write(1, "]\n", 2);
	
	// Print operations as numbers with "OpList: " prefix and square brackets
	write(1, "OpList: [", 9);
	print_operations_as_numbers(state);
	write(1, "]\n", 2);
}

void print_operations_as_numbers(t_sorting_state *state)
{
	t_list	*current;

	if (!state || !state->operations)
		return ;
	
	current = state->operations;
	while (current != NULL)
	{
		t_operation op = *(t_operation*)current->content;
		if (op >= SA && op <= RRR)
		{
			ft_putnbr_fd(op, 1);
			if (current->next)
				write(1, " ", 1);
		}
		current = current->next;
	}
}