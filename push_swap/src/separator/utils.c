/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:35:00 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:29 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>

int	extract_stack_values_to_computation(t_stack *stack,
		t_lis_computation *computation)
{
	t_node	*current_node;
	int		index;

	current_node = get_head(stack);
	index = 0;
	while (index < computation->n)
	{
		computation->nodes[index] = current_node;
		computation->values[index] = get_content(current_node);
		current_node = get_next(current_node);
		index++;
	}
	return (0);
}

size_t	calculate_lis_length(t_node **lis_nodes)
{
	size_t	count;

	if (!lis_nodes)
		return (0);
	count = 0;
	while (lis_nodes[count] != NULL)
		count++;
	return (count);
}

bool	is_node_in_lis(t_node *node, t_node **lis_nodes, size_t lis_count)
{
	size_t	i;

	if (!node || !lis_nodes)
		return (false);
	i = 0;
	while (i < lis_count)
	{
		if (lis_nodes[i] == node)
			return (true);
		i++;
	}
	return (false);
}
