/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breaks_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:44:04 by ptison            #+#    #+#             */
/*   Updated: 2025/10/09 11:48:52 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"

static int	get_next_value_circular(t_node *current, t_stack *stack, int index,
		int size)
{
	if (index == size - 1)
		return (get_head(stack)->content);
	return (get_next(current)->content);
}

static bool	is_break(int current_value, int next_value)
{
	return (current_value > next_value);
}

int	get_count_of_breaks(t_stack *stack, int size)
{
	t_node	*current;
	int		breaks_count;
	int		index;
	int		current_value;
	int		next_value;

	current = get_head(stack);
	breaks_count = 0;
	index = 0;
	while (index < size)
	{
		current_value = current->content;
		next_value = get_next_value_circular(current, stack, index, size);
		if (is_break(current_value, next_value))
			breaks_count++;
		current = get_next(current);
		index++;
	}
	return (breaks_count);
}
