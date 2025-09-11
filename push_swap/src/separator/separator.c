/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/11 23:03:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/separator.h"
#include <stdlib.h>


void	push_non_lis_into_b(t_sorting_state *state)
{
	t_node_bool_array	*lis_nodes;
	int					size_a;
	int					min_b;
	int					max_b;
	bool				has_b_range;
	int					i;
	t_node				*top;
	int					val;

	if (!state || !state->a)
		return ;
	
	lis_nodes = get_lis_nodes(state->a);
	if (!lis_nodes)
		return ;
	size_a = get_size(state->a);
	if (size_a <= 3)
	{
		free(lis_nodes->items);
		free(lis_nodes);
		return ;
	}
	
	// Initialize B range tracking
	min_b = 0;
	max_b = 0;
	has_b_range = false;
	
	// Process each element from top of stack A
	i = 0;
	while (i < size_a)
	{
		top = get_head(state->a);
		
		// Check if this node is part of the LIS
		bool is_lis_node = false;
		for (size_t j = 0; j < lis_nodes->count; j++)
		{
			if (lis_nodes->items[j].node == top)
			{
				is_lis_node = true;
				break;
			}
		}
		
		if (is_lis_node)
		{
			rotate_a(state);
		}
		else
		{
			push_b(state);
			
			// Apply B shaping (median rule)
			if (get_size(state->b) > 0)
			{
				val = get_content(get_head(state->b));
				if (!has_b_range)
				{
					min_b = val;
					max_b = val;
					has_b_range = true;
				}
				else
				{
					if (val < min_b)
						min_b = val;
					if (val > max_b)
						max_b = val;
				}
				int mid = (min_b + max_b) / 2;
				if (val < mid)
				{
					rotate_b(state);
				}
			}
		}
		
		i++;
	}
	
	free(lis_nodes->items);
	free(lis_nodes);
}
