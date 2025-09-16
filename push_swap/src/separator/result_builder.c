/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:35:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include <stdbool.h>
#include <stdlib.h>

void	reconstruct_lis_sequence_from_tracking(t_node **lis_nodes,
		t_lis_computation *computation, t_lis_result *computation_result)
{
	size_t	result_index;
	int		current_index;

	result_index = 0;
	current_index = computation_result->best_end;
	while (current_index != -1
		&& result_index < (size_t)computation_result->best_len)
	{
		lis_nodes[result_index] = computation->nodes[current_index];
		result_index++;
		current_index = computation->previous_indices[current_index];
	}
}

void	reverse_sequence_to_correct_order(t_node **lis_nodes, size_t lis_count)
{
	size_t	swap_index;
	t_node	*temporary_node;

	swap_index = 0;
	while (swap_index < lis_count / 2)
	{
		temporary_node = lis_nodes[swap_index];
		lis_nodes[swap_index] = lis_nodes[lis_count - 1 - swap_index];
		lis_nodes[lis_count - 1 - swap_index] = temporary_node;
		swap_index++;
	}
	lis_nodes[lis_count] = NULL;
}

t_node	**build_lis_result(t_lis_computation *computation,
		t_lis_result *computation_result, t_separator_arena *arena)
{
	t_node	**lis_nodes;

	if (!computation || !computation_result || !arena || !arena->lis_nodes)
		return (NULL);
	lis_nodes = arena->lis_nodes;
	reconstruct_lis_sequence_from_tracking(lis_nodes, computation,
		computation_result);
	reverse_sequence_to_correct_order(lis_nodes, computation_result->best_len);
	return (lis_nodes);
}
