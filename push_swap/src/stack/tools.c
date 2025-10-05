/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:48:36 by ptison            #+#    #+#             */
/*   Updated: 2025/10/05 20:31:10 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/stack.h"

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

int	find_min_index(t_stack *stack)
{
	int		min_index;
	int		min_value;
	int		current_index;
	t_node	*current_node;

	if (!stack || get_size(stack) <= 0)
		return (0);
	min_index = 0;
	min_value = get_content(get_head(stack));
	current_node = get_head(stack);
	current_index = 0;
	while (current_node != NULL)
	{
		if (get_content(current_node) < min_value)
		{
			min_value = get_content(current_node);
			min_index = current_index;
		}
		current_node = get_next(current_node);
		current_index++;
	}
	return (min_index);
}
