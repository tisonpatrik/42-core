/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:48:36 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 20:53:38 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/stack.h"
#include <stdbool.h>
#include <stdlib.h>

void	clear_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	if (!stack)
		return ;
	current = get_head(stack);
	while (current)
	{
		next = get_next(current);
		free(current);
		current = next;
	}
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
}

void	fill_stack(t_stack *stack, int *numbers, int n)
{
	t_node	*node;
	int		i;

	clear_stack(stack);
	i = n - 1;
	while (i >= 0)
	{
		node = create_node(numbers[i]);
		push_to_stack(stack, node);
		i--;
	}
}

bool	is_sorted(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	if (!stack || get_size(stack) <= 1)
		return (true);
	current = get_head(stack);
	next = get_next(current);
	while (next != NULL)
	{
		if (get_content(current) > get_content(next))
			return (false);
		current = next;
		next = get_next(current);
	}
	return (true);
}


void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	clear_stack(stack);
	free(stack);
}